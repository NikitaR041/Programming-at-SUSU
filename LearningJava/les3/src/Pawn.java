import java.util.ArrayList;
import java.util.List;

public class Pawn extends ChessFigure{
    public Pawn(char x, int y) {
        super(x,y);
    }
    //Переопределение метода
    @Override
    public boolean canKill(ChessFigure other) {
        return (Math.abs(other.x - this.x) == 1) && (other.y - this.y == 1);
    }
}
