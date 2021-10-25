#include <tuple>
#include <array>
#include <iostream>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#include <cassert>

struct TrainingPoint {
  uint8_t oxygenation;
  uint8_t acid_concentration;
};

struct Training {
  int id;
  int user_id;
  bool start_date; // should be QDateTime or something
  bool end_date;
  std::vector<TrainingPoint> points; // QVector maybe

  std::vector<char> points_into_blob() const {
    auto blob = std::vector<char>();

    for (const auto& point : points) {
      blob.push_back(point.oxygenation);
      blob.push_back(point.acid_concentration);
    }

    return blob;
  }

  void set_points_from_blob(const std::vector<char>& blob) {
    assert(!blob.empty());
    assert(blob.size() % 2 == 0);
    points.clear();
    points.reserve(blob.size() / 2);

    TrainingPoint point;
    size_t member_n = 0;
    for (const auto& b : blob) {
      assert(member_n <= 1);
      if (member_n == 0) {
        point.oxygenation = b;
        member_n += 1;
      } else if (member_n == 1) {
        point.acid_concentration = b;
        points.push_back(point);
        member_n = 0;
      }
    }
  }

  std::string points_into_string() const {
    std::string str = "[";
    for (const auto& p : points)
      str += fmt::format("{{{},{}}}", p.oxygenation, p.acid_concentration);
    return str + "]";
  }
};

using db_type = decltype(sqlite_orm::make_storage(
  ":memory:",
  sqlite_orm::make_table(
    "trainings",
    sqlite_orm::make_column("id",
                            &Training::id,
                            sqlite_orm::autoincrement(),
                            sqlite_orm::primary_key()),
    sqlite_orm::make_column("user_id", &Training::user_id),
    sqlite_orm::make_column("start_date", &Training::start_date),
    sqlite_orm::make_column("end_date", &Training::end_date),
    sqlite_orm::make_column("points",
                            &Training::points_into_blob,
                            &Training::set_points_from_blob))));

int main() {
  try {
    fmt::print("hello\n");
    fmt::print("sqlite version: {}\n", sqlite3_version);

    // --------------------------------------------------------------------
    // ----------------------------------------------- set up db and tables

    db_type storage = sqlite_orm::make_storage(
      ":memory:",
      sqlite_orm::make_table(
        "trainings",
        sqlite_orm::make_column("id",
                                &Training::id,
                                sqlite_orm::autoincrement(),
                                sqlite_orm::primary_key()),
        sqlite_orm::make_column("user_id", &Training::user_id),
        sqlite_orm::make_column("start_date", &Training::start_date),
        sqlite_orm::make_column("end_date", &Training::end_date),
        sqlite_orm::make_column("points",
                                &Training::points_into_blob,
                                &Training::set_points_from_blob)));
    storage.sync_schema();

    // --------------------------------------------------------------------
    // ----------------------------------------------- insert trainings

    auto t1 = Training{
      -1, 14, false, true, { { 56, 5 }, { 34, 3 }, { 65, 1 }, { 100, 4 } }
    };
    auto inserted_id_1 = storage.insert(t1);
    fmt::print("inserted_id_1: {}\n", inserted_id_1);

    auto t2 = Training{
      -1, 65, true, true, { { 23, 1 }, { 23, 2 }, { 99, 4 }, { 56, 2 } }
    };
    auto inserted_id_2 = storage.insert(t2);
    fmt::print("inserted_id_2: {}\n", inserted_id_2);

    // --------------------------------------------------------------------
    // ----------------------------------------------- get all trainings in db

    const auto trainings = storage.get_all<Training>();
    for (const auto& training : trainings) {
      fmt::print("selected id: {}; user_id: {}; points: {}\n",
                 training.id,
                 training.user_id,
                 training.points_into_string());
    }

    // --------------------------------------------------------------------

  } catch (std::exception e) {
    fmt::print("exception: {}", e.what());
  }
  return 0;
}
