import java.io.FileInputStream;
import java.text.ParseException;

public class myTest {
   /* private static void printTree(Tree parser) {
        System.out.printf("%s ->", parser.getNode());
        for(int i = 0 ; i < parser.children.size(); i ++){
            printTree(parser.children.get(i));
        }
        if (parser.children.size() == 0){
            System.out.printf("END");
        }

    }*/

    public static void main(String[] args) {
        FileInputStream myFile;
        try {
            myFile = new FileInputStream("/home/samariddin/homework/MT/src/test");
            Parser par = new Parser();
            par.parser(myFile);
          //  printTree(par.parser(myFile));
        } catch (ParseException e) {
            System.out.printf("%s %d\n", e, e.getErrorOffset());
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
