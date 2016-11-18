import java.io.*;
import java.util.*;
class Maze {
    private int height = 3;
    private int width = 3;
    private int N = 1;
    private int S = 2;
    private int E = 4;
    private int W = 8;
    private Map DX = new HashMap();
    private Map DY = new HashMap();
    private Map OPPOSITE = new HashMap();
    private List < Integer > directions = Arrays.asList(N, S, E, W);
    private int[][] grid = new int[height][width];
    long seed = System.nanoTime();

    public void mapping() {
        DX.put(E, 1);
        DX.put(W, -1);
        DX.put(N, 0);
        DX.put(S, 0);

        DY.put(E, 0);
        DY.put(W, 0);
        DY.put(N, -1);
        DY.put(S, 1);

        OPPOSITE.put(E, W);
        OPPOSITE.put(W, E);
        OPPOSITE.put(N, S);
        OPPOSITE.put(S, N);
    }

    public boolean between(int i, int minValueInclusive, int maxValueInclusive) {
        if (i >= minValueInclusive && i <= maxValueInclusive)
            return true;
        else
            return false;
    }

    public void printArray(int[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                System.out.print(grid[i][j] + " ");
            }
            System.out.println();
        }
    }

    public void printMaze(int[][] grid) {
        System.out.println(" " + new String(new char[width * 2 - 1]).replace("\0", "_"));
        for (int y = 0; y < height; y++) {
            System.out.print("|");
            for (int x = 0; x < width; x++) {
                System.out.print(((grid[y][x] & S) != 0) ? " " : "_");
                if ((grid[y][x] & E) != 0) {
                    System.out.print((((grid[y][x] | grid[y][x + 1]) & S) != 0) ? " " : "_");
                } else {
                    System.out.print("|");
                }
            }
            System.out.println();
        }
    }

    public void carve_passage_from(int cx, int cy, int[][] grid) {
        Collections.shuffle(directions, new Random());

        for (Integer direction: directions) {
            int nx = cx + (int) DX.get(direction);
            int ny = cy + (int) DY.get(direction);
            /*
            System.out.println("dir= " + direction +
            "("+Integer.toBinaryString(direction)+")"+
            ", cx= "+cx+", cy= "+cy+", nx= " + nx + ", ny= "+ ny);
            */
            if (between(ny, 0, grid.length - 1) && between(nx, 0, grid[1].length - 1) && (grid[ny][nx] == 0)) {
                grid[cy][cx] |= direction;
                grid[ny][nx] |= (int) OPPOSITE.get(direction);
                //printArray(grid);
                //System.out.println("______________");
                carve_passage_from(nx, ny, grid);
            }
        }
    }

    public void initGrid(int width, int height) {
        this.width = width;
        this.height = height;
    }

    public static void main(String[] args) throws java.lang.Exception {
        Maze maze = new Maze();
        //maze.initGrid(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        maze.mapping();
        maze.carve_passage_from(0, 0, maze.grid);
        maze.printMaze(maze.grid);
    }
}
