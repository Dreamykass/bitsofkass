import 'dart:ui';

import 'package:shared_preferences/shared_preferences.dart';

SharedPreferences? _prefs;

Future<void> prefsInit() async {
  _prefs = await SharedPreferences.getInstance();
}

SharedPreferences prefsInstance() {
  return _prefs!;
}

Size? prefsGetWindowSize() {
  double? w = prefsInstance().getDouble("window_size_w");
  double? h = prefsInstance().getDouble("window_size_h");
  if (w != null && h != null) {
    return Size(w, h);
  } else {
    return null;
  }
}

void prefsSetWindowSize(Size size) {
  prefsInstance().setDouble("window_size_w", size.width);
  prefsInstance().setDouble("window_size_h", size.height);
}

Offset? prefsGetWindowOffset() {
  double? x = prefsInstance().getDouble("window_offset_x");
  double? y = prefsInstance().getDouble("window_offset_y");
  if (x != null && y != null) {
    return Offset(x, y);
  } else {
    return null;
  }
}

void prefsSetWindowOffset(Offset offset) {
  prefsInstance().setDouble("window_offset_x", offset.dx);
  prefsInstance().setDouble("window_offset_y", offset.dy);
}

List<String> prefsGetBulbAddresses() {
  return prefsInstance().getStringList("bulb_addresses") ?? [];
}

void prefsSetBulbAddresses(List<String> addresses) {
  prefsInstance().setStringList("bulb_addresses", addresses);
}
