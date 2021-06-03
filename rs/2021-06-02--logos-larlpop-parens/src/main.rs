use lalrpop_util::lalrpop_mod;
use logos::Logos;
use serde::{Deserialize, Serialize};

lalrpop_mod!(pub numbers);

#[derive(logos::Logos, Debug, PartialEq, Clone, Copy)]
pub enum LogosToken {
    #[token("(")]
    ParenLeft,

    #[token(")")]
    ParenRight,

    #[token(",")]
    Comma,

    #[regex("[0-9]+")]
    Number,

    #[error]
    #[regex(r"[ \t\n\f]+", logos::skip)]
    Error,
}

#[derive(Debug, PartialEq, Clone, Serialize, Deserialize)]
pub enum Token {
    ParenLeft,
    ParenRight,
    Comma,
    Number(i32),
}

#[derive(Debug, PartialEq, Clone, Serialize, Deserialize)]
pub enum SingleTokenOrVec {
    TokenSingle(Token),
    TokenVec(Vec<SingleTokenOrVec>),
}

fn main() {
    // let source = "7";
    // let source = "(, (5), (((2))), (6), (5), (6), )";
    let source = "(, (33), (66), (, (88), (33), (99), ), )";

    let mut lex = LogosToken::lexer(source);
    let mut lexed = Vec::<(usize, Token, usize)>::new();

    println!("\nlexed:");
    while let Some(t) = lex.next() {
        println!("  '{}' - {:?}", lex.slice(), t,);
        let t = match t {
            LogosToken::ParenLeft => Some(Token::ParenLeft),
            LogosToken::ParenRight => Some(Token::ParenRight),
            LogosToken::Comma => Some(Token::Comma),
            LogosToken::Number => Some(Token::Number(lex.slice().parse().unwrap())),
            _ => None,
        };
        if let Some(t) = t {
            lexed.push((lex.span().start, t, lex.span().end));
        }
    }

    println!("\nlexed2:");
    for t in &lexed {
        println!("{:?}", t.1);
    }

    println!("\nparsed result:");
    let par = numbers::CompleteParser::new().parse(lexed.into_iter().map(|x| x));
    println!("  {:?}", par);

    println!("\njson:");
    println!("{}", serde_json::to_string_pretty(&par.unwrap()).unwrap());

    println!("\n");
}
