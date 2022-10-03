package exam.prob3;


class Sum
{
	private int sum;

	public int get() {
		return sum;
	}

	public void set(int sum) {
		this.sum = sum;
	}
}

class SummationOne implements Runnable
{
	private int upper;
	private Sum sumValue;

	public SummationOne(int upper, Sum sumValue) {
		this.upper = upper;
		this.sumValue = sumValue;
	}

	@Override
	public void run() {
		int sum = 0;

		for (int i = 0; i <= upper; i++)
			sum += i;

		sumValue.set(sum);
	}
}


class SummationTwo implements Runnable
{
	private int upper;
	private Sum sumValue;

	public SummationTwo(int upper, Sum sumValue) {
		this.upper = upper;
		this.sumValue = sumValue;
	}

	@Override
	public void run() {
		int sum = 0;

		for (int i = 1; i <= upper; i++){
			sum += upper+i;
		}


		sumValue.set(sum);
	}
}

public class JavaThread
{
	public static void main(String[] args) {
		if (args.length != 1) {
			System.err.println("Usage Driver <integer>");
			System.exit(0);
		}
		
		if (Integer.parseInt(args[0]) < 0) {
			System.err.println(args[0] + " must be >= 0");
			System.exit(0);
		}

		// Create the shared object
		Sum sumObject = new Sum();
		Sum sumObjectTwo = new Sum();
		int upper = Integer.parseInt(args[0]);
		
		Thread worker = new Thread(new SummationOne(upper, sumObject));
		worker.start();
		Thread workerTwo = new Thread(new SummationTwo(upper, sumObjectTwo));
		workerTwo.start();
		try {
			worker.join();
			workerTwo.join();
		} catch (InterruptedException ie) { }
		

		
		int totalFinal = sumObject.get() + sumObjectTwo.get();
		System.out.println("The desired sum using " + upper + " is " + totalFinal);
	}
}
