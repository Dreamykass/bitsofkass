
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

int main()
{
  std::string username;
  std::cout << "hello, give username: ";
  std::cin >> username;

  auto response = cpr::Get(cpr::Url{"https://www.instagram.com/" + username + "/?__a=1"});
  std::cout << "status code: " << response.status_code << "\n";

  auto json = nlohmann::json::parse(response.text);
  std::cout << "id: " << json["graphql"]["user"]["id"] << "\n";
  return 0;
}

/*
import urllib.request
import json

with urllib.request.urlopen("https://www.instagram.com/" ... "/?__a=1") as response:
  print(json.loads(response.read())["logging_page_id"][12:])
  */