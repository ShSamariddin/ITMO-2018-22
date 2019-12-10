import java.util.ArrayList;
import java.util.List;

class Tree {
    private Token node;
    private String name;
    private int cnt;
    public  List<Tree> children;

    Tree(Token node, String name, int cnt) {
        this.children =  new ArrayList();
        this.node = node;
        this.name = name;
        this.cnt = cnt;
    }

    void addChild(Tree child) {
        this.children.add(child);
    }
    List<Tree> getChildren(){
        return children;
    }

    String getName() {
        return name;
    }

    Token getToken() {
        return node;
    }
    int getCnt(){return cnt;}


}
