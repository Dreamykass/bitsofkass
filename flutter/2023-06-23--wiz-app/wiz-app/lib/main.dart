import 'package:flutter/material.dart';
import 'package:flutter_circle_color_picker/flutter_circle_color_picker.dart';

import 'bulb.dart';
import 'layout.dart';

void main() {
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

class _MyHomePageState extends State<MyHomePage> {
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
  }

  @override
  void dispose() {
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

  Widget commandButton(
      String text, IconData icon, String command, bool enabled) {
    if (enabled) {
      return ElevatedButton.icon(
        icon: Icon(icon),
        label: Text(text),
        style: ElevatedButton.styleFrom(minimumSize: const Size.fromHeight(40)),
        onPressed: () {
          BulbManager().sendCommand(command);
        },
      );
    } else {
      return OutlinedButton.icon(
        icon: Icon(icon),
        label: Text(text),
        style: ElevatedButton.styleFrom(minimumSize: const Size.fromHeight(40)),
        onPressed: () {
          BulbManager().sendCommand(command);
        },
      );
    }
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
                (bulbState["sceneId"] == 14),
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
              commandButton(
                'warm',
                Icons.local_fire_department,
                '{"method":"setState","params":{"sceneId":11,"temp":2700}}',
                (bulbState["sceneId"] == 11),
              ),
              commandButton(
                'day',
                Icons.light_mode,
                '{"method":"setState","params":{"sceneId":12,"temp":4200}}',
                (bulbState["sceneId"] == 12),
              ),
              commandButton(
                'cold',
                Icons.ac_unit,
                '{"method":"setState","params":{"sceneId":13,"temp":6500}}',
                (bulbState["sceneId"] == 13),
              ),
              commandButton(
                'fireplace',
                Icons.fireplace,
                '{"method":"setState","params":{"sceneId":5}}',
                (bulbState["sceneId"] == 5),
              ),
            ],
          ),
          Center(
            child: CircleColorPicker(
              controller: _controller,
              onChanged: (color) {
                setState(() => _currentColor = color);
              },
              onEnded: (color) {
                final command =
                    '{"method":"setPilot","params":{"r":${color.red},"g":${color.green},"b":${color.blue}}}';
                BulbManager().sendCommand(command);
                // print(command);
                // RawDatagramSocket.bind(InternetAddress.anyIPv4, 38899)
                //     .then((socket) {
                //   //socket.broadcastEnabled = true;
                //   socket.send(utf8.encode(command),
                //       InternetAddress('192.168.0.165'), 38899);
                //   socket.close();
                // });
              },
            ),
          ),
        ],
      ),
    );
  }
}
