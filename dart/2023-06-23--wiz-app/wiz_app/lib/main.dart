import 'dart:io' show Platform;

import 'package:flutter/material.dart';
import 'package:flutter_circle_color_picker/flutter_circle_color_picker.dart';
import 'package:window_manager/window_manager.dart';
import 'package:wiz_app/prefs.dart';

import 'bulb.dart';
import 'layout.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await prefsInit();
  if (!Platform.isAndroid) await windowManager.ensureInitialized();
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      // theme: ThemeData(
      //   primarySwatch: Colors.purple,
      // ),
      theme: ThemeData.dark(),
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key});

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> with WindowListener {
  Color _currentColor = Colors.pink;
  final _controller = CircleColorPickerController(
    initialColor: Colors.pink,
  );

  Map<String, dynamic> bulbState = {};
  String bulbStateStr = "";
  double dimSliderValue = 20;
  double tempSliderValue = 2700;

  @override
  void initState() {
    super.initState();
    BulbManager().addListener(bulbManagerChanged);
    windowManager.addListener(this);

    var size = prefsGetWindowSize();
    if (size != null) {
      windowManager.setSize(size, animate: true);
    }

    var offset = prefsGetWindowOffset();
    if (offset != null) {
      windowManager.setPosition(offset, animate: true);
    }
  }

  @override
  void dispose() {
    windowManager.removeListener(this);
    BulbManager().removeListener(bulbManagerChanged);
    super.dispose();
  }

  void bulbManagerChanged() {
    setState(() {
      bulbStateStr = BulbManager().stateStr;
      bulbState = BulbManager().state;
      if (bulbState["dimming"] != null) {
        dimSliderValue = bulbState["dimming"].toDouble();
      }
      if (bulbState["temp"] != null) {
        tempSliderValue = bulbState["temp"].toDouble();
      }
    });
  }

  @override
  Future<void> onWindowResize() async {
    prefsSetWindowSize(await windowManager.getSize());
    prefsSetWindowOffset(await windowManager.getPosition());
  }

  @override
  Future<void> onWindowMoved() async {
    prefsSetWindowSize(await windowManager.getSize());
    prefsSetWindowOffset(await windowManager.getPosition());
  }

  Widget commandButton(String text, IconData icon, String command, bool enabled,
      {bool hasMinimumSize = true}) {
    if (enabled) {
      return ElevatedButton.icon(
        icon: Icon(icon),
        label: Text(text),
        style: ElevatedButton.styleFrom(
            minimumSize: hasMinimumSize ? const Size.fromHeight(40) : null),
        onPressed: () {
          BulbManager().sendCommand(command);
        },
      );
    } else {
      return OutlinedButton.icon(
        icon: Icon(icon),
        label: Text(text),
        style: ElevatedButton.styleFrom(
            minimumSize: hasMinimumSize ? const Size.fromHeight(40) : null),
        onPressed: () {
          BulbManager().sendCommand(command);
        },
      );
    }
  }

  Widget colorButton(int r, int g, int b) {
    return IconButton(
      icon: const Icon(Icons.circle),
      color: Color.fromRGBO(r, g, b, 1.0),
      onPressed: () {
        _controller.color = Color.fromRGBO(r, g, b, 1.0);
        var color = _currentColor;
        final command =
            '{"method":"setPilot","params":{"r":${color.red},"g":${color.green},"b":${color.blue}}}';
        BulbManager().sendCommand(command);
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: dynamicLayout(
        context: context,
        children: [
          Text(bulbStateStr),
          Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const SizedBox(width: 20, height: 20),
              OutlinedButton.icon(
                icon: const Icon(
                  Icons.code,
                ),
                label: const Text('state'),
                style: ElevatedButton.styleFrom(
                    minimumSize: const Size.fromHeight(40)),
                onPressed: () {
                  BulbManager().sendCommandGetState();
                },
              ),
              commandButton(
                'on',
                Icons.lightbulb,
                '{"method":"setState","params":{"state":true}}',
                (bulbState["state"] == true),
              ),
              commandButton(
                'off',
                Icons.lightbulb_outline,
                '{"method":"setState","params":{"state":false}}',
                (bulbState["state"] == false),
              ),
              commandButton(
                'night',
                Icons.nightlight,
                '{"method":"setState","params":{"sceneId":14}}',
                (bulbState["sceneId"] == 14) && (bulbState["state"]),
              ),
              Row(
                children: [
                  const Icon(
                    Icons.flare,
                  ),
                  Expanded(
                    child: Slider(
                      value: dimSliderValue,
                      min: 10,
                      max: 100,
                      divisions: 100,
                      // label: sliderValue.round().toString(),
                      onChanged: (double value) {
                        setState(() {
                          dimSliderValue = value;
                        });
                      },
                      onChangeEnd: (double value) {
                        setState(() {
                          dimSliderValue = value;
                        });
                        BulbManager().sendCommand(
                            '{"method":"setState","params":{"dimming":$value}}');
                      },
                    ),
                  ),
                  const Icon(
                    Icons.light_mode,
                  ),
                ],
              ),
              Row(
                children: [
                  const Icon(
                    Icons.local_fire_department,
                  ),
                  Expanded(
                    child: Slider(
                      value: tempSliderValue,
                      min: 2200,
                      max: 6500,
                      divisions: 100,
                      // label: sliderValue.round().toString(),
                      onChanged: (double value) {
                        setState(() {
                          tempSliderValue = value;
                        });
                      },
                      onChangeEnd: (double value) {
                        setState(() {
                          tempSliderValue = value;
                        });
                        BulbManager().sendCommand(
                            '{"method":"setState","params":{"temp":$value}}');
                      },
                    ),
                  ),
                  const Icon(
                    Icons.ac_unit,
                  ),
                ],
              ),
              Row(
                children: [
                  commandButton(
                    '',
                    Icons.hdr_weak,
                    '{"method":"setState","params":{"temp":2200,"dimming":10}}',
                    false,
                    hasMinimumSize: false,
                  ),
                  Expanded(
                    child: commandButton(
                      'hot',
                      Icons.hot_tub,
                      '{"method":"setState","params":{"temp":2200}}',
                      (bulbState["temp"] == 2200) && (bulbState["state"]),
                      hasMinimumSize: false,
                    ),
                  ),
                  commandButton(
                    '',
                    Icons.hdr_strong,
                    '{"method":"setState","params":{"temp":2200,"dimming":50}}',
                    false,
                    hasMinimumSize: false,
                  ),
                ],
              ),
              Row(
                children: [
                  commandButton(
                    '',
                    Icons.hdr_weak,
                    '{"method":"setState","params":{"sceneId":11,"temp":2700,"dimming":30}}',
                    false,
                    hasMinimumSize: false,
                  ),
                  Expanded(
                    child: commandButton(
                      'warm',
                      Icons.local_fire_department_sharp,
                      '{"method":"setState","params":{"sceneId":11,"temp":2700}}',
                      (bulbState["sceneId"] == 11) && (bulbState["state"]),
                      hasMinimumSize: false,
                    ),
                  ),
                  commandButton(
                    '',
                    Icons.hdr_strong,
                    '{"method":"setState","params":{"sceneId":11,"temp":2700,"dimming":75}}',
                    false,
                    hasMinimumSize: false,
                  ),
                ],
              ),
              Row(
                children: [
                  commandButton(
                    '',
                    Icons.hdr_weak,
                    '{"method":"setState","params":{"sceneId":12,"temp":4200,"dimming":50}}',
                    false,
                    hasMinimumSize: false,
                  ),
                  Expanded(
                    child: commandButton(
                      'day',
                      Icons.light_mode,
                      '{"method":"setState","params":{"sceneId":12,"temp":4200}}',
                      (bulbState["sceneId"] == 12) && (bulbState["state"]),
                      hasMinimumSize: false,
                    ),
                  ),
                  commandButton(
                    '',
                    Icons.hdr_strong,
                    '{"method":"setState","params":{"sceneId":12,"temp":4200,"dimming":100}}',
                    false,
                    hasMinimumSize: false,
                  ),
                ],
              ),
              commandButton(
                'cold',
                Icons.ac_unit,
                '{"method":"setState","params":{"sceneId":13,"temp":6500}}',
                (bulbState["sceneId"] == 13) && (bulbState["state"]),
              ),
              commandButton(
                'fireplace',
                Icons.fireplace,
                '{"method":"setState","params":{"sceneId":5}}',
                (bulbState["sceneId"] == 5) && (bulbState["state"]),
              ),
              TextFormField(
                decoration: const InputDecoration(
                  labelText: 'bulb addresses',
                ),
                initialValue: prefsGetBulbAddresses().join(","),
                onChanged: (text) {
                  prefsSetBulbAddresses(text.split(","));
                },
              ),
            ],
          ),
          Column(
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  colorButton(255, 0, 0),
                  colorButton(255, 12, 0),
                  colorButton(255, 24, 0),
                  colorButton(255, 36, 0),
                  colorButton(255, 48, 0),
                  colorButton(255, 60, 0),
                ],
              ),
              Center(
                child: CircleColorPicker(
                  controller: _controller,
                  onChanged: (color) {
                    setState(() => _currentColor = color);
                  },
                  onEnded: (color) {
                    var color = _currentColor;
                    final command =
                        '{"method":"setPilot","params":{"r":${color.red},"g":${color.green},"b":${color.blue}}}';
                    BulbManager().sendCommand(command);
                  },
                ),
              ),
            ],
          ),
        ],
      ),
    );
  }
}
