import 'dart:convert';
import 'dart:io';

import 'package:flutter/cupertino.dart';

class BulbManager extends ChangeNotifier {
  static final BulbManager _instance = BulbManager._internal();

  RawDatagramSocket? socket;

  Map<String, dynamic> state = {};
  String stateStr = "";

  factory BulbManager() {
    return _instance;
  }

  BulbManager._internal() {
    RawDatagramSocket.bind(InternetAddress.anyIPv4, 38899).then((s) {
      //socket.broadcastEnabled = true;
      //socket.close();
      socket = s;

      socket?.listen((event) {
        //print("received: ${event.toString()}");
        var datagram = socket?.receive();
        if (datagram != null) {
          receiveDatagram(datagram);
        }
      });
      sendCommandGetState();
    });
  }

  String getPrettyJSONString(txt) {
    var obj = json.decode(txt);
    var encoder = const JsonEncoder.withIndent("     ");
    return encoder.convert(obj);
  }

  void receiveDatagram(Datagram datagram) {
    var decoded = utf8.decode(datagram.data);
    print("received: ${decoded}");
    if (decoded.contains('method":"getPilot"')) {
      stateStr = getPrettyJSONString(decoded);
      state = jsonDecode(decoded)["result"];
      // print(state.toString());
      notifyListeners();
    }
  }

  void sendCommandGetState() {
    var command = '{"method" : "getPilot"}';
    var encoded = utf8.encode(command);
    var address = InternetAddress('192.168.0.165');
    var port = 38899;
    socket?.send(encoded, address, port);
  }

  void sendCommand(String command) {
    print("sending: $command");

    var encoded = utf8.encode(command);
    var address = InternetAddress('192.168.0.165');
    var port = 38899;
    socket?.send(encoded, address, port);

    Future.delayed(const Duration(seconds: 1), () {
      sendCommandGetState();
    });
  }
}
