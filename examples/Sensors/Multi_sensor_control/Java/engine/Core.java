package engine;

import javax.swing.JFrame;

/**
 * Esta clase es el motor principal, cada metodo que quiera actualizarse debe heredar de aqui
 * Created by Jesus Garcia Urtiaga on 21/10/2015.
 */
public class Core extends Thread{

    protected Time time = new Time();

    private double ticks = 60D; //Ticks per second

    protected JFrame frame;

	private int ticksCount=0;
    private int fpsCount=0;

    protected Core() {
        // Exists only to defeat instantiation.
    }

    public void run(){
        double ns = 1000000000 / ticks;
        long lastTime = System.nanoTime();
        double perSecondTimer = 0;
        double delta = 0;

        while(true) {
            long now = System.nanoTime();
            delta += (now - lastTime) / ns;
            lastTime = now;
            while(delta >= 1d) {
                time.run();
                update();
                delta--;

                if(time.time>perSecondTimer){
                    perSecondTimer = time.time + 1;
                    updateEverySecond();
                    //System.out.println(ticksCount + " ticks, " + fpsCount + " fps " );
                    ticksCount = 0;
                    fpsCount = 0;
                }
                ticksCount++;
            }

            try {
                Thread.sleep(2);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            fpsCount++;
        }

    }

    protected void updateEverySecond(){

    }

    protected void update(){//Engine.Time runs every tick
    	if(frame!=null){
	    	frame.getContentPane().removeAll();
			
	    	draw();
			
			frame.repaint();
    	}
    }
    
    protected void draw(){
    	
    }

    protected  void pause(int millis){
        try {
            Thread.sleep(millis);
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public int getTicksCount() {
        return ticksCount;
    }

    public int getFpsCount() {
        return fpsCount;
    }
    
    public double getTicks() {
		return ticks;
	}

	public void setTicks(double ticks) {
		this.ticks = ticks;
	}
	
	public void destroy(){
		frame.dispose();
		this.stop();
	}

}