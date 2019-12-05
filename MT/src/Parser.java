import com.sun.jdi.ThreadReference;
import com.sun.security.jgss.GSSUtil;

import java.io.FileInputStream;
import java.text.ParseException;

public class Parser {
    LexicalAnalyzer lex;

    /*Tree C() throws ParseException {
        Tree curTree;
        Token  curToken  = lex.curToken;
        System.out.println("C");
        System.out.println(curToken);
        if(curToken == Token.COMMA){
            curTree = new Tree(",");
            lex.nextToken();
            curTree.addChild(B());
            return curTree;
        } else if(curToken == Token.COLON){
            lex.nextToken();
            if(lex.curToken == Token.TYPE){
                lex.nextToken();
                if(lex.curToken == Token.SEMICOLON){
                    System.out.println(":TYPE;");
                    curTree = new Tree(":TYPE;");
                    lex.nextToken();
                    System.out.println(lex.curToken);
                    if(lex.curToken != Token.END){
                        curTree.addChild(B());
                        return curTree;
                    }
                    return curTree;
                }
            }
        }
        throw new ParseException("mistake" + lex.curToken, lex.curPos);
    }
    Tree B() throws ParseException {
        Tree curTree = new Tree("B");
        Token curToken = lex.curToken;
        System.out.printf("VAR %s\n", curToken);
        if(curToken == Token.VARIABLE){
            curTree.addChild(new Tree("VARIABLE"));
        } else{
            throw  new ParseException("VARIABLE" + lex.curChar , lex.curPos);
        }
        lex.nextToken();
        curTree.addChild(C());
        return curTree;
    }*/

    Tree D() throws  ParseException{
        Tree curTree = new Tree(Token.TERMINAL, "D");
        Token curToken = lex.curToken;
        if(curToken == Token.END){
            curTree.addChild(new Tree(Token.END, "END"));
        } else{
            curTree.addChild(new Tree(To));
        }
    }

    Tree C() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "C");
        Token curToken = lex.curToken;
        if (curToken == Token.SEMICOLON) {
            curTree.addChild(new Tree(Token.SEMICOLON, ";"));
        } else {
            throw  new ParseException("Exceptin in function C", lex.curPos);
        }
        curTree.addChild(D());
        return curTree;
    }

    Tree B() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "B");
        Token curToken = lex.curToken;
        if (curToken == Token.TYPE) {
            curTree.addChild(new Tree(Token.TYPE, lex.getName()));
        } else {
            throw new ParseException("Exception in function B", lex.curPos);
        }
        curTree.addChild(C());
        return curTree;

    }

    Tree A() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "A");
        Token curToken = lex.curToken;
        if (curToken == Token.COMMA) {
            curTree.addChild(new Tree(Token.COMMA, ","));
            curTree.addChild(T());
        } else if (curToken == Token.COLON) {
            curTree.addChild(new Tree(Token.COLON, ":"));
            curTree.addChild(B());
        } else {
            throw new ParseException("exception in Terminla A", lex.curPos);
        }
    }

    Tree T() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "T");
        Token curToken = lex.curToken;
        if (curToken == Token.VARIABLE) {
            curTree.addChild(new Tree(Token.VARIABLE, lex.curName.toString()));
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

    Tree S() throws ParseException {
        Tree curTree = new Tree(Token.TERMINAL, "S");
        Token curToken = lex.curToken;
//        System.out.printf("C %s\n", curToken);
        if (curToken == Token.VAR) {
            curTree.addChild(new Tree(Token.VAR, "var"));
        } else {
            throw new ParseException("exception at the beginning", lex.curPos);
        }

        lex.nextToken();
        curTree.addChild(T());
        return curTree;
    }

    public void parser(FileInputStream myFile) throws ParseException {
        lex = new LexicalAnalyzer(myFile);
        lex.nextToken();
        while (lex.curToken != Token.END) {
            System.out.printf("%s ", lex.curName);
            if (lex.curName.toString().equals(";")) {
                System.out.println();
            }
            lex.nextToken();
        }
//        return S();
    }

}
