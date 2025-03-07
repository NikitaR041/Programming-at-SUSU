import java.util.ArrayList;
import java.util.List;

public class Pawn extends ChessFigure{
    public Pawn(int x, int y) {
        super(x,y);
    }
    @Override
    public List<int[]> getAttackPositions() {
        List<int[]> positions = new ArrayList<>();

        // Пешка атакует по диагонали на одну клетку вперед
        if (y + 1 <= 8) {
            if (x - 1 >= 1) positions.add(new int[]{x - 1, y + 1});
            if (x + 1 <= 8) positions.add(new int[]{x + 1, y + 1});
        }
        return positions;
    }
    @Override
    public String toString() {
        return "Пешка на позиции ("+x+' '+ y+')';
    }
}
