import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.security.spec.ECField;
import java.sql.SQLOutput;
import java.text.ParseException;

public class LexicalAnalyzer {
    InputStream is;
    int curChar;
    StringBuilder curName;
    boolean sign = true;
    boolean firstWord = true;
    boolean beforeWasСolon = false;
    int fl;
    int curPos;
    Token curToken;

    public LexicalAnalyzer(InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        curToken = Token.START;
        fl = 0;
        nextChar();
    }

    private boolean isBlank(int c) {
        return (c == ' ' || c == '\r' || c == '\n' || c == '\t');
    }
    private boolean isType(String str){
        return (str.equals("integer") || str.equals("char") || str.equals("string"));
    }
    private void nextChar() throws ParseException {
        curPos++;
        try {
            curChar = is.read();
        } catch (IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    private boolean is_val(int c) {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '0') || (c == '_'));
    }

    private char lowerCase(int curChar) {
        if (curChar >= 'A' && curChar <= 'Z') {
            return (char) (curChar - ('A' - 'a'));
        } else {
            return (char) curChar;
        }
    }

    public void nextToken() throws ParseException {
        while (isBlank(curChar)) {
            nextChar();
        }
        if (curChar == -1) {
            curToken = Token.END;
            return;
        }
        switch (curChar){
            case ':':
                curToken = Token.COLON;
                curName = new StringBuilder();
                curName.append(':');
                nextChar();
                return ;
            case ',':
                curToken = Token.COMMA;
                curName = new StringBuilder();
                curName.append(',');
                nextChar();
                return;
            case ';':
                curToken = Token.SEMICOLON;
                curName = new StringBuilder();
                curName.append(';');
                nextChar();
                return ;
        }
        curName = new StringBuilder();
        while (is_val(curChar)) {
            curName.append(lowerCase(curChar));
            nextChar();
        }
        if (!is_val(curChar) && !isBlank(curChar) && curChar != ':' && curChar != ',' && curChar != ';') {
            throw new ParseException("Illegal character "
                    + (char) curChar, curPos);
        }
        if (firstWord) {
            if (!curName.toString().equals("var")) {
                throw new ParseException("Illegal start "
                        + curName.toString(), 0);
            }
            curToken = Token.VAR;
            firstWord = false;
            return;
        }
        if(isType(curName.toString())){
            curToken = Token.TYPE;
        } else{
            curToken = Token.VARIABLE;
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos();
    }

    String getName(){
        return curName.toString();
    }

    /*public static void main(String[] args) {
        FileInputStream myFile;
        try {
            myFile = new FileInputStream("/home/samariddin/homework/MT/src/test");
            LexicalAnalyzer my = new LexicalAnalyzer(myFile);
            while(my.curToken != Token.END){
                System.out.println(my.curToken);
                my.nextToken();
            }

        } catch (ParseException e) {
            System.out.printf("%s %d\n" , e, e.getErrorOffset());
        } catch (Exception e){
            System.out.println(e);
        }
    }*/
}

