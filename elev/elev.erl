-module(elev).
-compile([export_all]).
-on_load(init/0).

init() ->
    ok = erlang:load_nif("./ebin/elev", 0).

set_speed(_X) ->
    exit(nif_library_not_loaded).

set_door_open_lamp(_X) ->
    exit(nif_library_not_loaded).

set_stop_lamp(_X) ->
    exit(nif_library_not_loaded).

set_floor_indicator(_X) ->
    exit(nif_library_not_loaded).

set_button_lamp(_X,_Y,_Z) ->
    exit(nif_library_not_loaded).

get_obstruction_signal() ->
    exit(nif_library_not_loaded).

get_stop_signal() ->
    exit(nif_library_not_loaded).

get_floor_sensor_signal() ->
    exit(nif_library_not_loaded).

get_button_signal(_X,_Y) ->
    exit(nif_library_not_loaded).

elev_init() ->
    exit(nif_library_not_loaded).
