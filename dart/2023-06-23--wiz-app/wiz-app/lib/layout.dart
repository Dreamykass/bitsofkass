import 'package:flutter/cupertino.dart';

Widget dynamicLayout({
  required BuildContext context,
  required List<Widget> children,
}) {
  if (MediaQuery.of(context).size.width > 900) {
    return Row(
      children: children
          .map((child) => Expanded(child: SingleChildScrollView(child: child)))
          .toList(),
    );
  } else {
    return SingleChildScrollView(
      child: Column(children: children),
    );
  }
}
