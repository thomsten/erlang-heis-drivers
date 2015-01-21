#include "erl_nif.h"
#include "elev.h"

static ERL_NIF_TERM 
elev_set_speed_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int value;
  if (!enif_get_int(env, argv[0], &value)) {
    return enif_make_badarg(env);
  }
  elev_set_speed(value);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM 
elev_set_door_open_lamp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int value;
  if (!enif_get_int(env, argv[0], &value)) {
      return enif_make_badarg(env);
  }
  elev_set_door_open_lamp(value);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM 
elev_get_obstruction_signal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  return enif_make_int(env, elev_get_obstruction_signal());
}

static ERL_NIF_TERM 
elev_get_stop_signal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  return enif_make_int(env, elev_get_stop_signal());
}

static ERL_NIF_TERM 
elev_set_stop_lamp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int value;
  if (!enif_get_int(env, argv[0], &value)) {
    return enif_make_badarg(env);
  }
  elev_set_stop_lamp(value);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM 
elev_get_floor_sensor_signal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  return enif_make_int(env, elev_get_floor_sensor_signal());
}

static ERL_NIF_TERM
elev_set_floor_indicator_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int floor;
  if (!enif_get_int(env, argv[0], &floor)) {
    return enif_make_badarg(env);
  }
  if (floor < 0 || floor >= N_FLOORS) {
    return enif_make_badarg(env);
  }
  elev_set_floor_indicator(floor);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM
elev_get_button_signal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int button, floor; // BUTTON: UP=0,DOWN=1,INTERNAL=2
  if (!enif_get_int(env, argv[0], &button) || !enif_get_int(env, argv[1], &floor)) {
    return enif_make_badarg(env);
  }
  
  // Lots of ugly if testing...
  if (floor < 0 || floor >= N_FLOORS) { // floor out of range
    return enif_make_badarg(env);
  }
  if (button == 0 && floor == N_FLOORS-1) { // Going up from top floor...
    return enif_make_badarg(env);
  }
  if (button == 1 && floor == 0) { // Going down from ground floor...
    return enif_make_badarg(env);
  }
  if (button < 0 || button > 2) { // Invalid button
    return enif_make_badarg(env);
  }
  
  switch (button) {
  case 0:
    return enif_make_int(env, elev_get_button_signal(BUTTON_CALL_UP, floor));
  case 1:
    return enif_make_int(env, elev_get_button_signal(BUTTON_CALL_DOWN, floor));
  case 2:
    return enif_make_int(env, elev_get_button_signal(BUTTON_COMMAND, floor));
  default:
    // How did you get here...?
    return enif_make_badarg(env);
    break;
  }
}

static ERL_NIF_TERM
elev_set_button_lamp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int button, floor, value; // BUTTON: UP=0,DOWN=1,INTERNAL=2
  if (!enif_get_int(env, argv[0], &button) || !enif_get_int(env, argv[1], &floor)
      || !enif_get_int(env, argv[2], &value)) {
    return enif_make_badarg(env);
  }
  
  // Lots of ugly if testing...
  if (floor < 0 || floor >= N_FLOORS) { // floor out of range
    return enif_make_badarg(env);
  }
  if (button == 0 && floor == N_FLOORS-1) { // Going up from top floor...
    return enif_make_badarg(env);
  }
  if (button == 1 && floor == 0) { // Going down from ground floor...
    return enif_make_badarg(env);
  }
  if (button < 0 || button > 2) { // Invalid button
    return enif_make_badarg(env);
  }
  
  switch (button) {
  case 0:
    elev_set_button_lamp(BUTTON_CALL_UP, floor, value);
    return enif_make_atom(env, "ok");
  case 1:
    elev_set_button_lamp(BUTTON_CALL_DOWN, floor, value);
    return enif_make_atom(env, "ok");
  case 2:
    elev_set_button_lamp(BUTTON_COMMAND, floor, value);
    return enif_make_atom(env, "ok");
  default:
    // How did you get here...?
    return enif_make_badarg(env);
    break;
  }
  // How did you get here...?
  return enif_make_badarg(env);  
}

static ERL_NIF_TERM
elev_init_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (elev_init()) {
    return enif_make_atom(env, "ok");
  } else {
    return enif_make_atom(env, "fail");
  }
}

static ErlNifFunc nif_funcs[] = {
  {"set_speed", 1, elev_set_speed_nif},
  {"set_door_open_lamp", 1, elev_set_door_open_lamp_nif},
  {"get_obstruction_signal", 0, elev_get_obstruction_signal_nif},
  {"get_stop_signal", 0, elev_get_stop_signal_nif},
  {"set_stop_lamp", 1, elev_set_stop_lamp_nif},
  {"get_floor_sensor_signal", 0, elev_get_floor_sensor_signal_nif},
  {"set_floor_indicator", 1, elev_set_floor_indicator_nif},
  {"get_button_signal", 2, elev_get_button_signal_nif},
  {"set_button_lamp", 3, elev_set_button_lamp_nif},
  {"elev_init", 0, elev_init_nif}
};

ERL_NIF_INIT(elev, nif_funcs, NULL, NULL, NULL, NULL)
