import java.util.ArrayList;
import java.util.List;

public class Knight extends ChessFigure{
    public Knight(char x, int y){
        super(x,y);
    }

    //Переопределение метода
    @Override
    public boolean canKill(ChessFigure other) {
        int dx = Math.abs(other.x - this.x);
        int dy = Math.abs(other.y - this.y);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
}

