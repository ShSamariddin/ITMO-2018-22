import java.io.FileInputStream;
import java.text.ParseException;

public class myTest {
    private static void printTree(Tree parser) {
        if(parser.getToken() != Token.TERMINAL) {
            System.out.printf("%s ", parser.getName());
        }
        for(int i = 0 ; i < parser.children.size(); i ++){
            printTree(parser.children.get(i));
        }
        if(parser.getToken() == Token.END){
            System.out.println("END");
        }

    }

    public static void main(String[] args) {
        FileInputStream myFile;
        try {
            myFile = new FileInputStream("/home/samariddin/homework/MT/src/test");
            Parser par = new Parser();
            //par.parser(myFile);
            Tree newT = par.parser(myFile);
            GraphViz
        } catch (ParseException e) {
            System.out.printf("%s %d\n", e, e.getErrorOffset());
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
