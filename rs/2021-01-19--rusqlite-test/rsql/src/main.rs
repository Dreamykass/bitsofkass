use rusqlite::{params, Connection};

#[derive(Debug)]
struct GunType {
    id: i32,
    name: String,
}

fn main() {
    let connection = Connection::open_in_memory().unwrap();

    connection
        .execute(
            "CREATE TABLE gun_type (
                  id              INTEGER PRIMARY KEY,
                  name            TEXT NOT NULL
                  )",
            params![],
        )
        .unwrap();

    {
        connection
            .execute(
                "INSERT INTO gun_type (name) VALUES (?1)",
                params!["shotgun"],
            )
            .unwrap();

        connection
            .execute("INSERT INTO gun_type (name) VALUES (?1)", params!["pistol"])
            .unwrap();

        connection
            .execute("INSERT INTO gun_type (name) VALUES (?1)", params!["rifle"])
            .unwrap();

        connection
            .execute(
                "INSERT INTO gun_type (name) VALUES (?1)",
                params!["flamethrower"],
            )
            .unwrap();
    }

    let mut statement = connection.prepare("SELECT id, name FROM gun_type").unwrap();
    let gun_types = statement
        .query_map(params![], |row| -> Result<(i64, String), _> {
            //
            Ok((row.get(0).unwrap(), row.get(1).unwrap()))
        })
        .unwrap()
        .map(|r| r.unwrap());

    for gun_type in gun_types {
        println!("gun_type: {:?}", gun_type);
    }
}
