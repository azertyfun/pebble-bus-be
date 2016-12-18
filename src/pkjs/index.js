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
                    stop['stop_point']['distance'] = dist;
                });


                // Order stops by distance (closest first)
                var stops = json['stop_schedules'].sort(function(a, b) {
                    return a['stop_point']['distance'] - b['stop_point']['distance'];
                });


                stops.forEach(function(stop) {
                    var n_next_busses = stop['date_times'].length;
                    var next_d = new Date(0), next_d2 = new Date(0);
                    if(n_next_busses > 0) {
                        var next_d = iso8601_to_date(stop['date_times'][0]['date_time']);
                        if(n_next_busses > 1)
                            var next_d2 = iso8601_to_date(stop['date_times'][1]['date_time']);
                    }
                    var stop_formatted = {
                        'ADD_STOP': stop['stop_point']['name'],
                        'ADD_STOP_LINE': stop['display_informations']['code'] + ' to ' + stop['display_informations']['direction'],
                        'ADD_STOP_NEXT': next_d.getTime() / 1000,
                        'ADD_STOP_SECOND_NEXT': next_d2.getTime() / 1000,
                    };

                    send(stop_formatted);
                });

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

