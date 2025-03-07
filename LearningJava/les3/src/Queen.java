import java.util.ArrayList;
import java.util.List;

public class Queen extends ChessFigure{
    public Queen(int x, int y){
        super(x, y);
    }

    @Override
    public List<int[]> getAttackPositions() {
        List<int[]> positions = new ArrayList<>();

        // Ферзь может ходить по горизонтали, вертикали и диагоналям
        for (int i = 1; i <= 8; i++) {
            if (i != x) positions.add(new int[]{i, y}); // Горизонталь
            if (i != y) positions.add(new int[]{x, i}); // Вертикаль
            if (x + i <= 8 && y + i <= 8) positions.add(new int[]{x + i, y + i}); // Диагональ вправо-вниз
            if (x - i >= 1 && y - i >= 1) positions.add(new int[]{x - i, y - i}); // Диагональ влево-вверх
            if (x + i <= 8 && y - i >= 1) positions.add(new int[]{x + i, y - i}); // Диагональ вправо-вверх
            if (x - i >= 1 && y + i <= 8) positions.add(new int[]{x - i, y + i}); // Диагональ влево-вниз
        }
        return positions;
    }

    @Override
    public String toString() {
        return "Королева на позиции ("+x+' '+ y+')';
    }
}
