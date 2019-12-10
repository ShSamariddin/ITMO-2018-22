import junit.framework.TestCase;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;

public class checker extends TestCase {
//    public void test5() throws ParseException, IOException {
//        FileInputStream readFile = new FileInputStream("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/test5");
//        Parser par = new Parser();
//        myTest test = new myTest();
//        StringBuilder ans = test.printTree(par.parser(readFile), new StringBuilder("http://mxwell.github.io/draw-graph/?q=graph{"), false);
//        ans.append("}#");
//        FileWriter writFile = new FileWriter("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/ans_test5");
//        writFile.append(ans.toString());
//        writFile.close();
//    }
//    public void test4() throws ParseException, IOException {
//        FileInputStream readFile = new FileInputStream("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/test4");
//        Parser par = new Parser();
//        myTest test = new myTest();
//        StringBuilder ans = test.printTree(par.parser(readFile), new StringBuilder("http://mxwell.github.io/draw-graph/?q=graph{"), false);
//        ans.append("}#");
//        FileWriter writFile = new FileWriter("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/ans_test4");
//        writFile.append(ans.toString());
//        writFile.close();
//    }
    public void test2() throws ParseException, IOException {
        FileInputStream readFile = new FileInputStream("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/test2");
        Parser par = new Parser();
        myTest test = new myTest();
        StringBuilder ans = test.printTree(par.parser(readFile), new StringBuilder("http://mxwell.github.io/draw-graph/?q=graph{"), false);
        ans.append("}#");

        FileWriter writFile = new FileWriter("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/ans_test2");
        writFile.append(ans.toString());
        writFile.close();
    }

//    public void test1() throws ParseException, IOException {
//        FileInputStream readFile = new FileInputStream("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/test1");
//        Parser par = new Parser();
//        myTest test = new myTest();
//        StringBuilder ans = test.printTree(par.parser(readFile), new StringBuilder("http://mxwell.github.io/draw-graph/?q=graph{"), false);
//        ans.append("}#");
//        FileWriter writFile = new FileWriter("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/ans_test1");
//        writFile.append(ans.toString());
//        writFile.close();
//    }
//
//    public void test() throws ParseException, IOException {
//        FileInputStream readFile = new FileInputStream("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/test");
//        Parser par = new Parser();
//        myTest test = new myTest();
//        StringBuilder ans = test.printTree(par.parser(readFile), new StringBuilder("http://mxwell.github.io/draw-graph/?q=graph{"), false);
//        ans.append("}#");
//        FileWriter writFile = new FileWriter("/home/samariddin/ITMO/ITMO-2018-19/MT2019/MT/src/tests/ans_test");
//        writFile.append(ans.toString());
//        writFile.close();
//    }

}
