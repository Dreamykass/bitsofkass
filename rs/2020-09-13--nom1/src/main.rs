extern crate nom;
// use nom::*;

// fn hello_parser(i: &str) -> nom::IResult<&str, &str> {
//     // alt!(i, tag!("hello") | tag!("goodbye"))
//     nom::branch::alt((
//         nom::bytes::complete::tag("hello"),
//         nom::bytes::complete::tag("goodbye"),
//     ))(i)
// }

// ---------------------------------------------------------------------------

enum WordOrList {
    Word(String),
    List(Vec<WordOrList>),
}

fn parse_to_word_or_list(s: &str) -> Result<WordOrList, &str> {
    // alt!(s, take_till!(char::is_alphabetic));
    // nom::branch::alt(nom::sequence::terminated(first: F, second: G)(nom::character::is_alphanumeric));

    return Err("fuck");
}

fn read_parsing_result(result: &Result<WordOrList, &str>) {
    match result {
        Err(why) => {
            println!("error: {}", why);
        }
        Ok(result) => {
            println!("result:");
            go_through_parsing_result(result, 0);
        }
    }
}

fn go_through_parsing_result(wol: &WordOrList, indent: u32) {
    let indent_str = str::repeat("", indent as usize);

    match wol {
        WordOrList::Word(word) => {
            println!("{}word: {}", indent_str, word);
        }

        WordOrList::List(list) => {
            println!("{}word:", indent_str);
            for elem in list {
                go_through_parsing_result(elem, indent + 1);
            }
        }
    }
}

// ---------------------------------------------------------------------------

fn main() {
    // println!("{:?}", hello_parser("hello"));
    // println!("{:?}", hello_parser("hello world"));
    // println!("{:?}", hello_parser("goodbye hello again"));
    println!("----------");

    read_parsing_result(&parse_to_word_or_list("hey"));

    println!("----------");
}
