import javafx.scene.web.WebView;

import javax.swing.text.StyledEditorKit;
import java.awt.*;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.text.ParseException;
import java.util.logging.Logger;

public class buildClick {

    public  StringBuilder printTree(Tree parser, StringBuilder ans, Boolean us) {
        for (int i = 0; i < parser.children.size(); i++) {
            StringBuilder curRes = new StringBuilder();
            if (us) {
                curRes.append(";");
            }

            curRes.append(parser.getToken());
            if (parser.getToken() == Token.TERMINAL || parser.getToken() == Token.TYPE || parser.getToken() == Token.VARIABLE) {
                curRes.append("_");
                curRes.append(parser.getName());
            }
            curRes.append("_");
            curRes.append(Integer.toString(parser.getCnt()));
            curRes.append("--");
            curRes.append(parser.children.get(i).getToken());
            if (parser.children.get(i).getToken() == Token.TERMINAL || parser.children.get(i).getToken() == Token.TYPE || parser.children.get(i).getToken() == Token.VARIABLE) {
                curRes.append("_");
                curRes.append(parser.children.get(i).getName());
            }
            curRes.append("_");
            curRes.append(Integer.toString(parser.children.get(i).getCnt()));
            ans.append(curRes);

            us = true;
            printTree(parser.children.get(i), ans, us);
        }
        return ans;
    }


}
