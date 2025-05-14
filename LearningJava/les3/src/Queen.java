import java.util.ArrayList;
import java.util.List;

public class Queen extends ChessFigure {
    public Queen(char x, int y) {
        super(x, y);
    }

    //Переопределение метода
    @Override
    public boolean canKill(ChessFigure other) {
        int dx = Math.abs(other.x - this.x);
        int dy = Math.abs(other.y - this.y);
        return this.x == other.x || this.y == other.y || dx == dy;
    }
}
