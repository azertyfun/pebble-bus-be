Pebble.addEventListener('ready', function(e) {
    console.log('Pebblekit JS ready!');

    var dict = {
        'MESSAGE': 'BEGIN'
    };

    send(dict);
});

var coords;

Pebble.addEventListener('appmessage', function(e) {
    console.log('AppMessage received!');
    console.log(JSON.stringify(e));

    if(e['payload'] != undefined && e['payload']['MESSAGE'] != undefined && e['payload']['MESSAGE'] == 'GET_STOPS') {

        var request = new XMLHttpRequest();
        request.onload = function() {

            var text = this.responseText;
            var r = /\\u([\d\w]{4})/gi;
            text = text.replace(r, function (match, grp) {
                return String.fromCharCode(parseInt(grp, 16));
            });
            text = unescape(text);

            try {
                var json = JSON.parse(text);

                var stops = []

                // Compute distance from user for each stop
                var R = 6371e3;
                var lat1 = coords.latitude * Math.PI / 180;
                var lon1 = coords.longitude * Math.PI / 180;
                json['stop_schedules'].forEach(function(stop) {
                    var lat2 = parseFloat(stop['stop_point']['coord']['lat']) * Math.PI / 180;
                    var lon2 = parseFloat(stop['stop_point']['coord']['lon']) * Math.PI / 180;

                    var dlat = (lat2 - lat1) * Math.PI / 180;
                    var dlon = (lon2 - lon1) * Math.PI / 180;

                    var a = Math.sin(dlat / 2) * Math.sin(dlat / 2) + Math.cos(lat1) * Math.cos(lat2) * Math.sin(dlon/2) * Math.sin(dlon/2);
                    var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
                    var dist = R * c;

                    if(!(stop['stop_point']['id'] in stops)) {
                        stops[stop['stop_point']['id']] = {
                            'lines': [
                                stop,
                            ],
                            'distance': dist,
                            'name': stop['stop_point']['name'],
                            'id': stop['stop_point']['id']
                        };
                    } else {
                        stops[stop['stop_point']['id']]['lines'].push(stop);
                    }
                });


                // Order stops by distance (closest first)
                stops = stops.sort(function(a, b) {
                    return a['distance'] - b['distance'];
                });


                Object.size = function(obj) {
                    var size = 0, key;
                    for(key in obj) {
                        if(obj.hasOwnProperty(key)) size++;
                    }
                    return size;
                };


                send({
                    "MESSAGE": "DATA_RECEIVED"
                });

                for(var stop in stops) {
                    stop = stops[stop];

                    var stop_formatted = {
                        'ADD_STOP': stop['id'],
                        'ADD_STOP_NAME': stop['name'],
                        'ADD_STOP_N_LINES': Object.size(stop['lines']),
                        'ADD_STOP_LINES_S': '',
                    };

                    var first = true;
                    stop['lines'].forEach(function(line) {
                        if(first) {
                            stop_formatted['ADD_STOP_LINES_S'] = line['display_informations']['code'];
                            first = false;
                        } else {
                            stop_formatted['ADD_STOP_LINES_S'] = stop_formatted['ADD_STOP_LINES_S'] + ', ' + line['display_informations']['code'];
                        }

                    });

                    send(stop_formatted);

                    // We send the lines separately from the stop because nested json objects are hard in C (and I couldn't find examples online)
                    stop['lines'].forEach(function(line) {
                        var next_d = new Date(0), next_d2 = new Date(0);

                        var n_next_busses = line['date_times'].length;
                        if(n_next_busses > 0) {
                            var next_d = iso8601_to_date(line['date_times'][0]['date_time']);
                            if(n_next_busses > 1)
                                var next_d2 = iso8601_to_date(line['date_times'][1]['date_time']);
                        }

                        var line_formatted = {
                            'ADD_LINE': line['display_informations']['code'] + ' to ' + line['display_informations']['direction'],
                            'ADD_LINE_STOP': stop['id'],
                            'ADD_LINE_NEXT': next_d.getTime() / 1000,
                            'ADD_LINE_SECOND_NEXT': next_d2.getTime() / 1000,
                        };

                        send(line_formatted);
                    });
                }

            } catch(err) {
                console.log('Error parsing JSON response: ' + err);
            }
        };


        var options = {
            enableHighAccuracy: true,
            maximumAge: 10000,
            timeout: 20000
        };

        navigator.geolocation.getCurrentPosition(function(pos) {
            send({
                "MESSAGE": "GEOLOC_DONE"
            });

            coords = pos.coords;
            request.open('GET', 'https://api.navitia.io/v1/coverage/be/coords/' + pos.coords.longitude + ';' + pos.coords.latitude + '/stop_schedules');
            request.setRequestHeader('Authorization', '54bf9618-c15a-4c8c-be68-f451b9b8b969');
            request.send();
        }, function(err) {
            console.log('Location error (' + err.code + '): ' + err.message);
        });

    }

});

function iso8601_to_date(iso) {
    return new Date(parseInt(iso.substring(0, 4)), parseInt(iso.substring(4, 6)) - 1, parseInt(iso.substring(6, 8)), parseInt(iso.substring(9, 11)), parseInt(iso.substring(11, 13)), parseInt(iso.substring(13, 15)), 0);
}

function send(dict) {
    Pebble.sendAppMessage(dict, function() { console.log('Message sent successfully: ' + JSON.stringify(dict)); }, function(e) { console.log('Message failed: ' + JSON.stringify(e) + ', retrying.'); send(dict); });
}

