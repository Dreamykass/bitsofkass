use logos::Logos;
// #[macro_use]
// extern crate lalrpop_util;

use lalrpop_util::lalrpop_mod;
lalrpop_mod!(pub numbers);

#[derive(logos::Logos, Debug, PartialEq, Clone, Copy)]
pub enum Token {
    // Tokens can be literal strings, of any length.
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

#[derive(Debug, PartialEq, Clone)]
pub enum SingleTokenOrVec {
    TokenSingle(Token),
    TokenVec(Vec<SingleTokenOrVec>),
}

fn main() {
    // let source = "7";
    // let source = "(, (5), (((2))), (6), (5), (6), )";
    let source = "(, (33), (66), (, (88), (33), (99), ), )";

    let mut lex = Token::lexer(source);
    let mut lexed = Vec::<Option<Result<(usize, Token, usize), ()>>>::new();

    println!("\nlexed:");
    while let Some(t) = lex.next() {
        println!("  '{}' - {:?}", lex.slice(), t,);
        lexed.push(Some(Ok((lex.span().start, t, lex.span().end))));
    }

    let lex = Token::lexer(source);

    println!("\nparsed result:");
    let par = numbers::CompleteParser::new().parse(lex.spanned().map(|(t, r)| (r.start, t, r.end)));
    println!("  {:?}", par);

    println!("\nparsed iter?:");
    for x in par {
        println!("  {:?}", x);
    }

    println!("\n");
}
