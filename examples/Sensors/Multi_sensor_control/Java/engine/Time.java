package engine;

/**
 * Created by Jesus Garcia Urtiaga on 21/10/2015.
 */
public class Time {

    public double time;

	private double lastTimer = 0d;

    public Time(){
        lastTimer = System.nanoTime();
    }

    public void run(){
        time += getDeltaTime();
        //System.out.println("Tiempo: "+ time);
    }

    public double getDeltaTime(){
        double r = System.nanoTime() - lastTimer;
        lastTimer = System.nanoTime();
        return r/1000000000f;
    }
    
    public double getTime() {
		return time;
	}

	public void setTime(double time) {
		this.time = time;
	}
}