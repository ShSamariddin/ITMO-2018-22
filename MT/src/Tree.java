import java.util.ArrayList;
import java.util.List;

class Tree {
    private Token node;
    private String name;
    public  List<Tree> children;

    Tree(Token node, String name) {
        this.children =  new ArrayList();
        this.node = node;
        this.name = name;
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


}
