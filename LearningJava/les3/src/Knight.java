import java.util.ArrayList;
import java.util.List;

public class Knight extends ChessFigure{
    public Knight(int x, int y){
        super(x,y);
    }

    @Override
    public List<int[]> getAttackPositions() {
        List<int[]> positions = new ArrayList<>();
        int[][] moves = {
                {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };

        for (int[] move : moves) {
            int newX = x + move[0];
            int newY = y + move[1];
            if (newX >= 1 && newX <= 8 && newY >= 1 && newY <= 8) {
                positions.add(new int[]{newX, newY});
            }
        }
        return positions;
    }
    @Override
    public String toString() {
        return "Конь на позиции ("+x+' '+ y+')';
    }
}

