use serde_json::{Number, Value};
use std::fs::{create_dir_all, File};
use std::io::{Read, Write};
use std::path::Path;

fn main() {
    let mut profiles = "".to_string();
    File::open(Path::new("config.json"))
        .unwrap()
        .read_to_string(&mut profiles)
        .unwrap();

    println!("loaded profiles: ");
    let profiles = serde_json::from_str::<Value>(&*profiles)
        .unwrap()
        .get("profiles")
        .unwrap()
        .as_array()
        .unwrap()
        .iter()
        .map(|v| v.as_str().unwrap().to_string())
        .inspect(|s| println!("  {}", s))
        .collect::<Vec<_>>();

    create_dir_all("_backup").unwrap();
    create_dir_all("_output").unwrap();
    println!();
    println!("created folders for backups and outputs");

    for profile in profiles {
        let profile_path = profile;
        let mut profile_raw_json_str = "".to_string();

        let profile_filename = Path::new(&profile_path)
            .file_name()
            .unwrap()
            .to_str()
            .unwrap()
            .to_string();

        File::open(Path::new(&*profile_path))
            .unwrap()
            .read_to_string(&mut profile_raw_json_str)
            .unwrap();

        let profile_raw_json_str = profile_raw_json_str;
        File::create(format!("_backup/{}", &profile_filename))
            .unwrap()
            .write_all(profile_raw_json_str.as_bytes())
            .unwrap();
        println!("created backup: {}", profile_filename);

        let mut profile_json = serde_json::from_str::<Value>(&*profile_raw_json_str).unwrap();

        #[allow(clippy::suspicious_map)]
        let count = profile_json
            .pointer_mut("/characters/pmc/Inventory/items")
            .unwrap()
            .as_array_mut()
            .unwrap()
            .iter_mut()
            .filter(|item| {
                [
                    "5449016a4bdc2d6f028b456f", // rouble
                    "5696686a4bdc2da3298b456a",
                    "569668774bdc2da2298b4568",
                ]
                .iter()
                .any(|it| *it == item.get("_tpl").unwrap().as_str().unwrap())
            })
            .map(|item| {
                let item = item.get_mut("upd").unwrap().as_object_mut().unwrap();
                item["StackObjectsCount"] = Value::Number(Number::from(500_000));
            })
            .count();

        println!("Modified this many stacks: {}", count);

        File::create(format!("_output/{}", &profile_filename))
            .unwrap()
            .write_all(
                serde_json::ser::to_string_pretty(&profile_json)
                    .unwrap()
                    .as_bytes(),
            )
            .unwrap();
    }
}
