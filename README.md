import java.util.Scanner;
import java.util.InputMismatchException;

public class StudentManager {
	private static final Scanner scanner = new Scanner(System.in);
	
	public static void main(String[] args) {
		 // 학생 정보 입력 받기
        String name = inputName();
        int koreanScore = inputScore("국어");
        int englishScore = inputScore("영어");
        int mathScore = inputScore("수학");
        
        // 1. 총점 및 평균 계산, 총점은 정수로 계산하되 평균은 실수형으로 계산할 것
        int totalScore = koreanScore + englishScore + mathScore;
        double averageScore = totalScore / 3.0;
        
        
        // 학점 계산
        char grade = calculateGrade(averageScore);
        
        // 결과 출력
       printResult(name, koreanScore, englishScore, mathScore, totalScore,averageScore, grade);
        
        scanner.close();
    }
    
    // 2. 이름 입력 메소드 (입력에 공백이 있는지 없는지 판단하여, 공백이 있으면 다시 입력받을 것)
    public static String inputName() {
    	while(true) {
    		System.out.print("이름을 입력하세요: ");
    		String name = scanner.nextLine();
    		
    		if(name.contains(" "))
    			System.out.println("공백이 포함되어 있습니다. 공백 없이 다시 입력하세요.");
    		else
    			return name;
    	}	
    }
    
    // 3. 점수 입력 메소드 (점수에 숫자 아닌 것이 입력 안되도록, 0-100 사이 숫자만 입력되도록 제한할 것)
    public static int inputScore(String subject) {
    	while(true) {
    		System.out.print(subject+" 점수를 입력하세요(0~100): ");
    		try {
    			int score = scanner.nextInt();
    			
    			if(score<0||score>100)
    				System.out.println("0~100사이 숫자만 입력하세요.");
    			else
    				return score;
    			} 
    		catch(InputMismatchException e) {
    			String ex = scanner.nextLine();
    			System.out.println("입력 오류. 숫자만 입력하세요.");
    			//scanner.nextLine();
    			continue;
    		}	
    	}
    }
    
    // 4. 학점 계산 메소드 (~ 90 A, ~ 80 B, ~70 C, ~ 60 D, 이하 F)
    public static char calculateGrade(double averageScore) {
    	char grade;
    	int score = (int) averageScore/10;
    	
    	switch(score) {
    	case 10:
    	case 9:
    		grade = 'A';
    		break;
    	case 8:
    		grade = 'B';
    		break;
    	case 7:
    		grade = 'C';
    		break;
    	case 6:
    		grade = 'D';
    		break;
    	default:
    		grade = 'F';
    	}
    	return grade;
    }
    
    // 5. 결과 출력 메소드
    public static void printResult(String name, int koreanScore, int englishScore, int mathScore, int totalScore, double averageScore, char grade) {
        System.out.println("\n==== 학생 성적 정보 ====");
        System.out.println("이름: " + name);
        System.out.println("국어: " + koreanScore);
        System.out.println("영어: " + englishScore);
        System.out.println("수학: " + mathScore);
        System.out.println("총점: " + totalScore);
        System.out.printf("평균: %.2f\n", averageScore);
        System.out.println("학점: " + grade);
    }
}

