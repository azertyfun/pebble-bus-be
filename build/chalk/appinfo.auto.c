#include "pebble_process_info.h"
#include "src/resource_ids.auto.h"

const PebbleProcessInfo __pbl_app_info __attribute__ ((section (".pbl_header"))) = {
  .header = "PBLAPP",
  .struct_version = { PROCESS_INFO_CURRENT_STRUCT_VERSION_MAJOR, PROCESS_INFO_CURRENT_STRUCT_VERSION_MINOR },
  .sdk_version = { PROCESS_INFO_CURRENT_SDK_VERSION_MAJOR, PROCESS_INFO_CURRENT_SDK_VERSION_MINOR },
  .process_version = { 1, 0 },
  .load_size = 0xb6b6,
  .offset = 0xb6b6b6b6,
  .crc = 0xb6b6b6b6,
  .name = "Bus Belgium",
  .company = "Azertyfun",
  .icon_resource_id = RESOURCE_ID_ICON,
  .sym_table_addr = 0xA7A7A7A7,
  .flags = PROCESS_INFO_PLATFORM_CHALK,
  .num_reloc_entries = 0xdeadcafe,
  .uuid = { 0x1E, 0x9A, 0x47, 0x32, 0x18, 0x4E, 0x4E, 0xB1, 0xA1, 0x7E, 0xC4, 0xDD, 0x04, 0xE1, 0xF6, 0xA6 },
  .virtual_size = 0xb6b6
};
