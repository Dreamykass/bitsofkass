import 'dart:io';

import 'package:flutter/material.dart';

import 'dir_struct_widget.dart';
import 'misc.dart';

void main() {
  runApp(const MyApp());
  logger.v("verbose");
  logger.d("debug");
  logger.i("info");
  logger.w("warning!");
  logger.e("error!");
  logger.wtf("wtf");

  final dir = Directory('F:/SOULSEEK/proper/04 - Atmospheric');
  final List<FileSystemEntity> entities =
      dir.listSync(recursive: true).toList();
  for (var e in entities) {
    logger.i('${e.absolute}');
  }
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData.dark(),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Column(
        children: <Widget>[
          const Center(
            child: Text(
              "Stuff",
            ),
          ),
          Expanded(
            child: dirStructWidget(),
          ),
        ],
      ),
    );
  }
}
