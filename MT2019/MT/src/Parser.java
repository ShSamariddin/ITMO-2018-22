

import java.io.FileInputStream;
import java.text.ParseException;

public class Parser {
    LexicalAnalyzer lex;
    private int cnt = 0;

    Tree D() throws  ParseException{
        Tree curTree = new Tree(Token.TERMINAL, "D",cnt++);
        Token curToken = lex.curToken;
        if(curToken == Token.END){
            curTree.addChild(new Tree(Token.END, "END", cnt++));
        } else if(curToken == Token.VAR) {
            curTree.addChild(S());
        } else{
            curTree.addChild(T());
        }
        return curTree;
    }

    private Tree C() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "C", cnt++);
        Token curToken = lex.curToken;
        if (curToken == Token.SEMICOLON) {
            curTree.addChild(new Tree(Token.SEMICOLON, ";", cnt++));
            lex.nextToken();
        } else {
            throw  new ParseException("Exceptin in function C", lex.curPos);
        }
        curTree.addChild(D());
        return curTree;
    }

    private Tree B() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "B", cnt++);
        Token curToken = lex.curToken;
        if (curToken == Token.TYPE) {
            curTree.addChild(new Tree(Token.TYPE, lex.getName(), cnt++));
            lex.nextToken();
        } else {
            throw new ParseException("Exception in function B", lex.curPos);
        }
        curTree.addChild(C());
        return curTree;

    }

    private Tree A() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "A", cnt++);
        Token curToken = lex.curToken;
        if (curToken == Token.COMMA) {
            curTree.addChild(new Tree(Token.COMMA, ",", cnt++));
            lex.nextToken();
            curTree.addChild(T());
        } else if (curToken == Token.COLON) {
            curTree.addChild(new Tree(Token.COLON, ":", cnt++));
            lex.nextToken();
            curTree.addChild(B());
        } else {
            throw new ParseException("exception in Terminla A " + lex.curToken, lex.curPos);
        }
        return curTree;
    }

    private Tree T() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "T", cnt++);
        Token curToken = lex.curToken;
        if (curToken == Token.VARIABLE) {
            curTree.addChild(new Tree(Token.VARIABLE, lex.curName.toString(), cnt++));
            lex.nextToken();
        } else {
            throw new ParseException("exception in function NewS", lex.curPos);
        }
        curTree.addChild(A());
        return curTree;
    }
//    public static void main(String[] args) {
//        FileInputStream myFile;
//        try {
//            myFile = new FileInputStream("/home/samariddin/homework/MT/src/test");
//            LexicalAnalyzer my = new LexicalAnalyzer(myFile);
//            while(my.curToken != Token.END){
//                System.out.println(my.curToken);
//                my.nextToken();
//            }
//
//        } catch (ParseException e) {
//            System.out.printf("%s %d\n" , e, e.getErrorOffset());
//        } catch (Exception e){
//            System.out.println(e);
//        }
//    }

    private Tree S() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "S", cnt++);
        Token curToken = lex.curToken;
//        System.out.printf("C %s\n", curToken);
        if (curToken == Token.VAR) {
            curTree.addChild(new Tree(Token.VAR, "var", cnt++));
        } else {
            throw new ParseException("exception at the beginning", lex.curPos);
        }

        lex.nextToken();
        curTree.addChild(T());
        return curTree;
    }

    public Tree parser(FileInputStream myFile) throws ParseException {
        lex = new LexicalAnalyzer(myFile);
        lex.nextToken();
        return S();
    }

}
