import java.util.Random;
class th extends Thread {
    int rounds;
    BarrierImpl b;
    private Random generator = new Random();

    public th(int rounds, BarrierImpl b) {
        this.rounds = rounds;
        this.b = b;
    }
    public void run() {
        System.out.println("hello from thread");

        try {
            Thread.sleep(generator.nextInt(500));
        } catch (java.lang.InterruptedException e) {}
        b.Barrier(rounds);
        System.out.println("exit barrier");
    }
}


class BarrierImpl {

    public BarrierImpl() {return;}

    public synchronized void Barrier (int rounds) {
            arrived_proc++;
        if (arrived_proc == 5*rounds) {
            arrived_proc = 0;
            notifyAll();
            mypredicate = 1;
            System.out.println("notify barrier");
        }
        else {
            System.out.println("wait barrier");
            // while (mypredicate == 0) {
                try { wait(); } 
                catch (InterruptedException ex) {return;}
            //}
        }
    }

    private int arrived_proc = 0;
    private int mypredicate = 0;

}

class MultiThreading { 
    static BarrierImpl b = new BarrierImpl();

    public static void main(String[] arg) {
        int rounds = Integer.parseInt(arg[0],10);
        for (int i = 0; i < rounds; i++){
        new th(rounds, b).start();
        new th(rounds, b).start();
        new th(rounds, b).start();
        new th(rounds, b).start();
        new th(rounds, b).start();

        }
    }
}
