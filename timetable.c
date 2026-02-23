#include <stdio.h>
#include <string.h>	
#include <windows.h>
#define MAX 100
	int i;

	char ceCourse[][30] = {
		"Analysis",
		"Phys for Eng",
		"Intro Computing",
		"Cir Analysis",
		"Boolean Algebra",
		"Digital Electronics",
		"Linear Algebra",
		"Programming1"
	};
	char ceTime[][30] = {
		"7-9am",
		"9-11am",
		"11-1pm",
		"1-3pm",
		"3-5pm",
		"5-7pm"
	};
	
	char ceDay[][30] = {
		"Monday",
		"Tuesday",
		"Wednessday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	
	
	
	int ceCourseCount = 8;
	int ceTimeCount = 6;
	int ceDayCount = 6;
		
		char course[MAX][30];
		char courseID[MAX][30];
		char time[MAX][20];
		char hall[MAX][20];
		char lecturer[MAX][30];
		char day[MAX][15];
		int count = 0;
	
	
	// to check if the course is valid for CE
	int isValidCECourse(char input[]) {
				for(i = 0; i< ceCourseCount; i++){
					if(strcmp(input, ceCourse[i]) == 0){
						return 1;
					}
				}
					return 0;
			}
	int isValidCETime(char input[]){
		        for(i = 0; i < ceTimeCount; i++ ){
		        	if(strcmp(input, ceTime[i]) == 0){
		        		return 1;
					}
				}
				
				return 0;
	       }
	int isValidCEDay(char input[]){
		for(i = 0; i < ceDayCount; i++){
			if(strcmp(input, ceDay[i]) == 0){
				return 1;
			}
		}
		 return 0;
	}
	       
int isClashWithinCE(
    char newCourse[],
    char newCourseID[],
    char newHall[],
    char newTime[],
    char newLecturer[],
    char newDay[]
) {
    for (i = 0; i < count; i++) {
        if (strcmp(lecturer[i], newLecturer) == 0 &&
            strcmp(time[i], newTime) == 0 &&
            strcmp(day[i], newDay) == 0) {
            return 1;
        }
    }
    return 0;
}
			
int isHallOccupiedCE(char newHall[], char newTime[], char newDay[]) {
    for (i = 0; i < count; i++) {
        if (strcmp(hall[i], newHall) == 0 &&
            strcmp(time[i], newTime) == 0 &&
            strcmp(day[i], newDay) == 0) {
            return 1;
        }
    }
    return 0;
}

void initCECSV() {
    FILE *fp = fopen("ce_timetable.csv", "r");

    if (fp == NULL) {
        // File does not exist ? create and add headers
        fp = fopen("ce_timetable.csv", "w");
        if (fp == NULL) {
            printf("ERROR: Cannot create CSV file.\n");
            return;
        }

        fprintf(fp, "Course,CourseID,Day,Time,Hall,Lecturer\n");
        fclose(fp);
    } else {
        fclose(fp);
    }
}

void saveCEToCSV(
    char course[],
    char courseID[],
    char day[],
    char time[],
    char hall[],
    char lecturer[]
) {
    FILE *fp = fopen("ce_timetable.csv", "a");

    if (fp == NULL) {
        printf("ERROR: Unable to open CSV file.\n");
        return;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
            course, courseID, day, time, hall, lecturer);

    fclose(fp);
}

			
	void addCourse() {
		char tempTime[20]; 
		char tempHall[20];
		char tempLecturer[30]; 
		char tempDay[15];
	    char tempCourse[30];
	    char tempCourseID[30];
	
		    printf("Enter course name : ");
		    fgets(tempCourse, 30, stdin);
		    tempCourse[strcspn(tempCourse, "\n")] = 0;
		    
	          
             
		    if(!isValidCECourse(tempCourse)){
		    	    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY); 
			        printf("ERROR: Course does not belong to CE department.\n");
			        SetConsoleTextAttribute(h, 7);
			        return;
		    }
		    
		    printf("\nEnter course ID : ");
		    fgets(tempCourseID, 30, stdin);
		    tempCourseID[strcspn(tempCourseID, "\n")] = 0;

	// function to add course
			    strcpy(course[count], tempCourse);
			
			    printf("Enter time (e.g., 7-9am): ");
			    fgets(tempTime, 20, stdin);
			    tempTime[strcspn(tempTime, "\n")] = 0;
			    
			    
			       if(!isValidCETime(tempTime)){
			       	
			        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
                    
			        printf("ERROR: This is not a valid School hour.\n");
					SetConsoleTextAttribute(h, 7);
			        return;
			    }
			
			    printf("Enter Hall: ");
			    fgets(tempHall, 30, stdin);
			    tempHall[strcspn(tempHall, "\n")] = 0;
			
			    printf("Enter Lecturer: ");
			    fgets(tempLecturer, 20, stdin);
			    tempLecturer[strcspn(tempLecturer, "\n")] = 0;
			    
			    printf("Enter Day: ");
			    fgets(tempDay, 20, stdin);
			    tempDay[strcspn(tempDay, "\n")] = 0;     
				
				    if(!isValidCEDay(tempDay)){
				    	
					    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
	                    
	                    printf("ERROR: This is not a valid Day.\n");
	                    SetConsoleTextAttribute(h, 7);
	                    return;
					}
			    	    		    
		        // --- Clash Checks ---
            if (isClashWithinCE(
            tempCourse,
            tempCourseID,
            tempHall,
            tempTime,
            tempLecturer,
            tempDay)) {
            	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("ERROR: Lecturer %s already has a class at %s on %s.\n",
               tempLecturer, tempTime, tempDay);
               SetConsoleTextAttribute(h, 7);
        return;
    }

    if (isHallOccupiedCE(tempHall, tempTime, tempDay)) {
        printf("ERROR: Hall %s is already occupied at %s on %s.\n",
               tempHall, tempTime, tempDay);
        return;
    }

    // --- Add course after passing checks ---
					    strcpy(course[count], tempCourse);
					    strcpy(courseID[count], tempCourseID);
					    strcpy(time[count], tempTime);
					    strcpy(hall[count], tempHall);
					    strcpy(lecturer[count], tempLecturer);
					    strcpy(day[count], tempDay);
					
					    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
                        
					    count++;
					    
					    saveCEToCSV(
							    tempCourse,
							    tempCourseID,
							    tempDay,
							    tempTime,
							    tempHall,
							    tempLecturer
);

					    printf("\nCourse added successfully.\n");
					    
					    SetConsoleTextAttribute(h, 7);
}
	
	// Function to display CE timetable
	void generateTimeTable() {
	
	    if(count == 0){
	        printf("\nNo course added yet.\n");
	        return;
	    }
	
	    printf("\nCE TimeTable\n");
	    
	     HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	    
	    printf("+----------------------+----------+------------+----------+----------------------+\n");
	    
	     printf("| %-20s | %-8s | %-8s | %-10s | %-10s | %-10s |\n",
	           "Course", "CourseID","Day", "Time", "Hall", "Lecturer");
			   
		printf("+----------------------+----------+------------+----------+----------------------+\n");
	
	
		       
	      for (i = 0; i < count; i++) {
	        printf("| %-20s | %-8s | %-8s |%-10s | %-10s | %-10s |\n",
	               course[i], courseID[i], day[i], time[i], hall[i], lecturer[i]);
	    printf("+----------------------+----------+------------+----------+----------------------+\n");
	    } 
		 SetConsoleTextAttribute(h, 7);     
	}
	void Computer_Engieering () {
		initCECSV();
	    int option;
	
	    while(1) {
	        printf("\n1. Add course\n2. Generate timetable\n3. Exit\nChoose option: ");
	        scanf("%d", &option);
	        getchar(); // consume leftover newline
	
	        if(option == 1)
	            addCourse();
	        else if(option == 2)
	            generateTimeTable();
	        else if(option == 3)
	            break;
	        else
	            printf("Invalid option. Try again.\n");
	    }
	}
	
	
// FOR THE ELECTRICAL AND ELCTRONICS DEPARTMENT//	
	
	char eeCourse[][30] = {
		"Signals & Systems",
		"Analysis",
		"Phys for Eng",
		"Fundamentals",
		"Cir Analysis",
		"Programming1",
		"Digital El",
		"Power System"
	};
	
	char eeTime[][30] = {
		"7-9am",
		"9-11am",
		"11-1pm",
		"1-3pm",
		"3-5pm",
		"5-7pm"
	};
	
	char eeDay[][30] = {
		"Monday",
		"Tuesday",
		"Wednessday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	
	int eeCourseCount = 8;
	int eeTimeCount = 6;
	int eeDayCount = 6;
	
	char ee_Course[MAX][30];
	char ee_CourseID[MAX][30];
	char ee_Time[MAX][20];
	char ee_Hall[MAX][20];
	char ee_Lecturer[MAX][20];
	char ee_Day[MAX][15];
	int ee_count = 0;
	
	            // HERE I AM CHECKING ALL INPUT VALIDATIONS AND ENTRIES
	
					int isValidEECourse(char input[]){
						for(i = 0; i < eeCourseCount; i++){
							if(strcmp(input, eeCourse[i]) == 0){
								return 1;
							}
						}
						return 0;
					}
					
						int isValidEETime(char input[]){
						for(i = 0; i < eeTimeCount; i++){
							if(strcmp(input, eeTime[i]) == 0){
								return 1;
							}
						}
						return 0;
					}
					
						int isValidEEDay(char input[]){
						for(i = 0; i < eeDayCount; i++){
							if(strcmp(input, eeDay[i]) == 0){
								return 1;
							}
						}
						return 0;
					}
					
					// HERE I AM CHECKING IF COURSES WILL CLASH
	
				int isClashWithinEE(
				    char newee_Course[],
				    char newee_Hall[],
				    char newee_Time[],
				    char newee_Lecturer[],
				    char newee_Day[]
				) {
				    for (i = 0; i < ee_count; i++) {
				        if (strcmp(ee_Lecturer[i], newee_Lecturer) == 0 &&
				            strcmp(ee_Time[i], newee_Time) == 0 &&
				            strcmp(ee_Day[i], newee_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
							
				int isHallOccupiedEE(char newee_Hall[], char newee_Time[], char newee_Day[]) {
				    for (i = 0; i < ee_count; i++) {
				        if (strcmp(ee_Hall[i], newee_Hall) == 0 &&
				            strcmp(ee_Time[i], newee_Time) == 0 &&
				            strcmp(ee_Day[i], newee_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
				
       // THIS IS WHERE THE CSV FILE TRANSPORTATION AND EXPORTATIONS BEGINS
       
			void initEECSV() {
			    FILE *fp = fopen("EE_timetable.csv", "r");
			
			    if (fp == NULL) {
			        // File does not exist ? create and add headers
			        fp = fopen("EE_timetable.csv", "w");
			        if (fp == NULL) {
			            printf("ERROR: Cannot create CSV file.\n");
			            return;
			        }
			
			        fprintf(fp, "Course,CourseID,Day,Time,Hall,Lecturer\n");
			        fclose(fp);
			    } else {
			        fclose(fp);
			    }
			}
			
			void saveEEToCSV(
			    char ee_course[],
			    char ee_courseID[],
			    char ee_day[],
			    char ee_time[],
			    char ee_hall[],
			    char ee_lecturer[]
			)
			 {
			    FILE *fp = fopen("EE_timetable.csv", "a");
			
			    if (fp == NULL) {
			        printf("ERROR: Unable to open CSV file.\n");
			        return;
			    }
			
			    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
			            ee_course, ee_courseID, ee_day, ee_time, ee_hall, ee_lecturer);
			
			    fclose(fp);
			}
			
			// THIS IS WHERE I AM ADDING MY COURSES
	
 void addEECourse(){
 	  char temp_eecourse[30];
 	  char temp_eecourseID[30];
 	  char temp_eetime[30];
 	  char temp_eeday[30];
 	  char temp_eelecturer[30];
 	  char temp_eehall[30];
 	  
 	  
 	            printf("Enter Course Name :");
 	            fgets(temp_eecourse, 30, stdin);
 	            temp_eecourse[strcspn(temp_eecourse, "\n")] = 0;
 	            
 	            
 	               if(!isValidEECourse(temp_eecourse)){
 	               	    
 	               	    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
                        
 	               	    printf("Error! : Course not found in Department of Electrical and Electronics Engineeering ");
 	               	    SetConsoleTextAttribute(h, 7);
 	               	      return;     
					}
					
					
							printf("Enter Course ID :");
			 	            fgets(temp_eecourseID, 30, stdin);
			 	            temp_eecourseID[strcspn(temp_eecourseID, "\n")] = 0;
					
				 
							 printf("Enter Time : ");
							 fgets(temp_eetime, 30, stdin);
							 temp_eetime[strcspn(temp_eetime, "\n")] = 0;
							 
								   if(!isValidEETime(temp_eetime)){
	 	               	            
	 	               	            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
			 	               	    printf("Error! : This is not a valid time \n");
			 	               	    SetConsoleTextAttribute(h, 7);
			 	               	    return;     
								}
							 
							 printf("Enter Hall : ");
							 fgets(temp_eehall, 15, stdin);
							 temp_eehall[strcspn(temp_eehall, "\n")] = 0;
							 
							 printf("Enter Lecturer Name : ");
							 fgets(temp_eelecturer, 20, stdin);
							 temp_eelecturer[strcspn(temp_eelecturer, "\n")] = 0;
							 
							 printf("Enter Day : ");
							 fgets(temp_eeday, 30, stdin);
							 temp_eeday[strcspn(temp_eeday, "\n")] = 0;
							 
							   if(!isValidEEDay(temp_eeday)){
 	               	    
 	               	                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                                    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
                                    
			 	               	    printf("Error! : This is not a valid Day \n");
			 	               	    
			 	               	    SetConsoleTextAttribute(h, 7);
			 	               	    return;     
								}
								
								                    // COURSE CLASH IMPLEMENTATION FOR ALL THE COURSES ADDED
								                    
												     if (isClashWithinEE(
												            temp_eecourse,
												            temp_eehall,
												            temp_eetime,
												            temp_eelecturer,
												            temp_eeday)) {
												        printf("ERROR: Lecturer %s already has a class at %s on %s.\n",
												               temp_eelecturer, temp_eetime, temp_eeday);
												        return;
												    }
				
												     if (isHallOccupiedEE(temp_eehall, temp_eetime, temp_eeday)) {
												        printf("ERROR: Hall %s is already occupied at %s on %s.\n",
												               temp_eehall, temp_eetime, temp_eeday);
												        return;
												    }	  
								
													 
															HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
									                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
				
				                                            // Add course after passing checks 
															strcpy(ee_Course[ee_count], temp_eecourse);
															strcpy(ee_CourseID[ee_count], temp_eecourseID);
												            strcpy(ee_Time[ee_count], temp_eetime);
														    strcpy(ee_Hall[ee_count], temp_eehall);
														    strcpy(ee_Lecturer[ee_count], temp_eelecturer);
														    strcpy(ee_Day[ee_count], temp_eeday);
														     ee_count++;
						
						    
																     saveEEToCSV(
																	    temp_eecourse,
																	    temp_eecourseID,
																	    temp_eeday,
																	    temp_eetime,
																	    temp_eehall,
																	    temp_eelecturer
																    );	
			                        
								    printf("\nCourse added successfully.\n");
								    
								    SetConsoleTextAttribute(h, 7);
							 							 				 	  
 }
 
 // TIME RABLE GENERATOR
 
 void generateEETimeTable(){
 	
 	 
 	     if(ee_count == 0){
 	     	printf("\n No Course added yet.");
 	     	return;
		  }
 	            
 	 
 	              printf("\n EE TimeTable\n");
 	              
 	               HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                   SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				   
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				  
				  printf("| %-20s |  %-8s  | %-8s | %-10s | %-8s | %-20s |\n",
	                     "Course", "CourseID", "Day", "Time", "Hall", "Lecturer");
	                     
	              printf("+----------------------+----------+------------+----------+----------------------+\n");
 	              
 	              for(i = 0; i < ee_count; i++){
 	              	printf("| %-20s | %-8s | %-8s | %-10s | %-8s | %-20s |\n",
					       ee_Course[i], ee_CourseID[i], ee_Day[i], ee_Time[i], ee_Hall[i], ee_Lecturer[i]);
					       
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				  
				   }  
				    SetConsoleTextAttribute(h, 7);    
 	 
           }
           
void Electrical_Engineering(){
	initEECSV();
	int option;
	
	while(1){
		
		printf("\n1. Add course\n2. Generate timetable\n3. Exit\nChoose option: ");
        scanf("%d", &option);
        getchar(); 
        
        
        if(option == 1)
        	addEECourse();
        	
		else if(option == 2)
			generateEETimeTable();
			
		else if(option == 3)
			break;
	    
	    else 
	       printf("n Ivalide option/choice, select agian");
	}
	
}
 
 char meCourse[][30] = {
 	
 	"Analysis",
 	"Phys for Eng",
 	"programming1",
 };
 
 char meTime[][30] = {
 		"7-9am",
		"9-11am",
		"11-1pm",
		"1-3pm",
		"3-5pm",
		"5-7pm"
 };
 
 char meDay[][30] = {
 	    "Monday",
		"Tuesday",
		"Wednessday",
		"Thursday",
		"Friday",
		"Saturday"
 };
 
    int meCourseCount = 3;
    int meTimeCount = 6;
    int meDayCount = 6;
 
 	char me_course[MAX][30];
 	char me_courseID[MAX][30];
	char me_time[MAX][20];
	char me_hall[MAX][20];
	char me_lecturer[MAX][20];
	char me_day[MAX][15];
	int me_count = 0;
	
	
	                int isValidMECourse(char input[]){
	                	for(i = 0; i < meCourseCount; i++){
	                		if(strcmp(input, meCourse[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
					 int isValidMETime(char input[]){
	                	for(i = 0; i < meTimeCount; i++){
	                		if(strcmp(input, meTime[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
					 int isValidMEDay(char input[]){
	                	for(i = 0; i < meDayCount; i++){
	                		if(strcmp(input, meDay[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
					
					
					
								// HERE I AM CHECKING IF COURSES WILL CLASH
	
				int isClashWithinME(
				    char newme_Course[],
				    char newme_Hall[],
				    char newme_Time[],
				    char newme_Lecturer[],
				    char newme_Day[]
				) {
				    for (i = 0; i < me_count; i++) {
				        if (strcmp(me_lecturer[i], newme_Lecturer) == 0 &&
				            strcmp(me_time[i], newme_Time) == 0 &&
				            strcmp(me_day[i], newme_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
							
				int isHallOccupiedME(char newme_Hall[], char newme_Time[], char newme_Day[]) {
				    for (i = 0; i < me_count; i++) {
				        if (strcmp(me_hall[i], newme_Hall) == 0 &&
				            strcmp(me_time[i], newme_Time) == 0 &&
				            strcmp(me_day[i], newme_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
					
					
					
					//FOR THE CSV FILE 
			void initMECSV() {
					    FILE *fp = fopen("ME_timetable.csv", "r");
					
					    if (fp == NULL) {
					        // File does not exist ? create and add headers
					        fp = fopen("ME_timetable.csv", "w");
					        if (fp == NULL) {
					            printf("ERROR: Cannot create CSV file.\n");
					            return;
					        }
					
					        fprintf(fp, "Course,CourseID,Day,Time,Hall,Lecturer\n");
					        fclose(fp);
					    } else {
					        fclose(fp);
					    }
					}
					
					void saveMEToCSV(
					    char me_course[],
					    char me_courseID[],
					    char me_day[],
					    char me_time[],
					    char me_hall[],
					    char me_lecturer[]
					)
					 {
					    FILE *fp = fopen("ME_timetable.csv", "a");
					
					    if (fp == NULL) {
					        printf("ERROR: Unable to open CSV file.\n");
					        return;
					    }
					
					    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
					            me_course, me_courseID, me_day, me_time, me_hall, me_lecturer);
					
					    fclose(fp);
					}
					
 
 
     void addMeCourse(){
 	        char Me_tempCourse[30];
 	        char Me_tempCourseID[30];
 		    char Me_tempTime[30];
 			char Me_tempHall[30];
 			char Me_tempLecturer[30];
 			char Me_tempDay[30];
     	
     	        printf("Enter Course Name : ");
 	            fgets(Me_tempCourse, 30, stdin);
 	            Me_tempCourse[strcspn(Me_tempCourse, "\n")] = 0;
 	            
 	              if(!isValidMECourse(Me_tempCourse)){
 	               	    
 	               	    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
                        
 	               	    printf("Error! : Course not found in Department of Mechanical Engineeering ");
 	               	    SetConsoleTextAttribute(h, 7);
 	               	      return;     
					}
					
								printf("Enter Course ID : ");
				 	            fgets(Me_tempCourseID, 30, stdin);
				 	            Me_tempCourseID[strcspn(Me_tempCourseID, "\n")] = 0;
					
				 
							 printf("Enter Time : ");
							 fgets(Me_tempTime, 20, stdin);
							 Me_tempTime[strcspn(Me_tempTime, "\n")] = 0;
							 
									 if(!isValidMETime(Me_tempTime)){
									 	
		 	               	                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                                            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
					 	               	    printf("Error! : This is not a valid School hour \n");
					 	               	    SetConsoleTextAttribute(h, 7);
					 	               	    return;     
										}				
							 
							 printf("Enter Hall : ");
							 fgets(Me_tempHall, 20, stdin);
							 Me_tempHall[strcspn(Me_tempHall, "\n")] = 0;
							 
							 printf("Enter Lecturer Name : ");
							 fgets(Me_tempLecturer, 20, stdin);
							 Me_tempLecturer[strcspn(Me_tempLecturer, "\n")] = 0;
							 
							 printf("Enter Day : ");
							 fgets(Me_tempDay, 20, stdin);
							 Me_tempDay[strcspn(Me_tempDay, "\n")] = 0;
							 
									 if(!isValidMEDay(Me_tempDay)){
		 	               	    
				 	               	    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
				 	               	    printf("Error! : This is not a valid Day \n");
				 	               	    SetConsoleTextAttribute(h, 7);  
				 	               	    return;
							       }
							 
		                        
		                           // COURSE CLASH IMPLEMENTATION FOR ALL THE COURSES ADDED
								                    
												     if (isClashWithinEE(
												            Me_tempCourse,
												            Me_tempHall,
												            Me_tempTime,
												            Me_tempLecturer,
												            Me_tempDay)) {
												        printf("ERROR: Lecturer %s already has a class at %s on %s.\n",
												               Me_tempLecturer, Me_tempTime, Me_tempDay);
												        return;
												    }
				
												     if (isHallOccupiedEE(Me_tempHall, Me_tempTime, Me_tempDay)) {
												        printf("ERROR: Hall %s is already occupied at %s on %s.\n",
												               Me_tempHall, Me_tempTime, Me_tempDay);
												        return;
												    }	
		                        
		                                                   HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		                                                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
		                          // Add course after passing checks 
															strcpy(me_course[me_count], Me_tempCourse);
															strcpy(me_courseID[me_count], Me_tempCourseID);
															strcpy(me_time[me_count], Me_tempTime);
															strcpy(me_hall[me_count], Me_tempHall);
															strcpy(me_lecturer[me_count], Me_tempLecturer);
															strcpy(me_day[me_count], Me_tempDay);
												            
														     me_count++;
						
						    
																     saveMEToCSV(
																	    Me_tempCourse,
																	    Me_tempCourseID,
																	    Me_tempDay,
																	    Me_tempTime,
																	    Me_tempHall,
																	    Me_tempLecturer
																    );
							
							    printf("\nCourse added successfully.\n");
							    SetConsoleTextAttribute(h, 7);
	 }
    
    
     void generateMETimeTable(){

 	 
 	     if(me_count == 0){
 	     	printf("\n No Course added yet.");
 	     	return;
		  }
 	 
 	              HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
 	              printf("\n ME TimeTable\n");
				   
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				  
				  printf("| %-20s | %-8s | %-8s | %-10s | %-8s | %-20s|\n",
	                     "Course","CourseID", "Day", "Time", "Hall", "Lecturer");
	                     
	              printf("+----------------------+----------+------------+----------+----------------------+\n");
 	              
 	              for(i = 0; i < me_count; i++){
 	              	printf("| %-20s | %-8s | %-8s | %-10s | %-8s | %-20s|\n",
					       me_course[i], me_courseID[i], me_day[i], me_time[i], me_hall[i], me_lecturer[i]);
					       
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				   } 
				    SetConsoleTextAttribute(h, 7);     
 	 
           }
           
           
    void Mechanical_Engineering(){
	            initMECSV();
				int option;
				
				while(1){
					
					printf("\n1. Add course\n2. Generate timetable\n3. Exit\nChoose option: ");
			        scanf("%d", &option);
			        getchar(); 
			        
			        
			        if(option == 1)
			        	addMeCourse();
			        	
					else if(option == 2)
						generateMETimeTable();
						
					else if(option == 3)
						break;
				    
				    else 
				       printf("n Ivalide option/choice, select agian");
			}
				
	}
	
	
	char civCourse[][30] = {
	 	"Analysis",
	 	"Phys for Eng",
	 	"programming1",
 };
 
    char civTime[][30] = {
        "7-9am",
		"9-11am",
		"11-1pm",
		"1-3pm",
		"3-5pm",
		"5-7pm"
	};
	
	char civDay[][30] = {
		"Monday",
		"Tuesday",
		"Wednessday",
		"Thursday",
		"Friday",
		"Saturday"
		
	};
 
    int civCourseCount = 3;
    int civTimeCount = 6;
    int civDayCount = 6;
 
 	char civ_course[MAX][30];
 	char civ_courseID[MAX][30];
	char civ_time[MAX][15];
	char civ_hall[MAX][15];
	char civ_lecturer[MAX][15];
	char civ_day[MAX][15];
	int civ_count = 0;
	
	
	                int isValidCIVCourse(char input[]){
	                	for(i = 0; i < civCourseCount; i++){
	                		if(strcmp(input, civCourse[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
                     
                     int isValidCIVTime(char input[]){
	                	for(i = 0; i < civTimeCount; i++){
	                		if(strcmp(input, civTime[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
					 int isValidCIVDay(char input[]){
	                	for(i = 0; i < civDayCount; i++){
	                		if(strcmp(input, civDay[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
												// HERE I AM CHECKING IF COURSES WILL CLASH
	
				int isClashWithinCIV(
				    char newciv_Course[],
				    char newciv_CourseID[],
				    char newciv_Hall[],
				    char newciv_Time[],
				    char newciv_Lecturer[],
				    char newciv_Day[]
				) {
				    for (i = 0; i < civ_count; i++) {
				        if (strcmp(civ_lecturer[i], newciv_Lecturer) == 0 &&
				            strcmp(civ_time[i], newciv_Time) == 0 &&
				            strcmp(civ_day[i], newciv_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
							
				int isHallOccupiedCIV(char newciv_Hall[], char newciv_Time[], char newciv_Day[]) {
				    for (i = 0; i < civ_count; i++) {
				        if (strcmp(civ_hall[i], newciv_Hall) == 0 &&
				            strcmp(civ_time[i], newciv_Time) == 0 &&
				            strcmp(civ_day[i], newciv_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
					
					
					    // THIS IS WHERE THE CSV FILE TRANSPORTATION AND EXPORTATIONS BEGINS
       
			void initCIVCSV() {
			    FILE *fp = fopen("CIV_timetable.csv", "r");
			
			    if (fp == NULL) {
			        // File does not exist ? create and add headers
			        fp = fopen("CIV_timetable.csv", "w");
			        if (fp == NULL) {
			            printf("ERROR: Cannot create CSV file.\n");
			            return;
			        }
			
			        fprintf(fp, "Course,CourseID,Day,Time,Hall,Lecturer\n");
			        fclose(fp);
			  }   else {
			        fclose(fp);
			    }
			}
			
			void saveCIVToCSV(
			    char civ_course[],
			    char civ_courseID[],
			    char civ_day[],
			    char civ_time[],
			    char civ_hall[],
			    char civ_lecturer[]
			)
			 {
			    FILE *fp = fopen("CIV_timetable.csv", "a");
			
			    if (fp == NULL) {
			        printf("ERROR: Unable to open CSV file.\n");
			        return;
			    }
			
			    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
			            civ_course, civ_courseID, civ_day, civ_time, civ_hall, civ_lecturer);
			
			    fclose(fp);
			}
					
 
     void addCivCourse(){
     	char civ_tempCourse[30];
     	char civ_tempCourseID[30];
     	char civ_tempTime[30];
     	char civ_tempHall[30];
     	char civ_tempLecturer[30];
     	char civ_tempDay[30];
     	
     	        printf("Enter Course Name : ");
 	            fgets(civ_tempCourse, 30, stdin);
 	            civ_tempCourse[strcspn(civ_tempCourse, "\n")] = 0;
 	            
 	              if(!isValidCIVCourse(civ_tempCourse)){
 	               	    
 	               	    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
 	               	    printf("Error! : Course not found in Department Engineering\n");
 	               	    SetConsoleTextAttribute(h, 7);     
					}
					        
					        printf("Enter Course ID : ");
			 	            fgets(civ_tempCourseID, 30, stdin);
			 	            civ_tempCourseID[strcspn(civ_tempCourseID, "\n")] = 0;
				 
							 printf("Enter Time : ");
							 fgets(civ_tempTime, 30, stdin);
							 civ_tempTime[strcspn(civ_tempTime, "\n")] = 0;
							 
							  if(!isValidCIVTime(civ_tempTime)){  
 	               	    
				 	               	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
			 	               	    printf("Error! : This is not a valid School Hour \n");
			 	               	    SetConsoleTextAttribute(h, 7); 
									return;    
								}
							 
							 printf("Enter Hall : ");
							 fgets(civ_tempHall, 30, stdin);
							 civ_tempHall[strcspn(civ_tempHall, "\n")] = 0;
							 
							 printf("Enter Lecturer Name : ");
							 fgets(civ_tempLecturer, 30, stdin);
							 civ_tempLecturer[strcspn(civ_tempLecturer, "\n")] = 0;
							 
							 printf("Enter Day : ");
							 fgets(civ_tempDay, 30, stdin);
							 civ_tempDay[strcspn(civ_tempDay, "\n")] = 0;
							 
							  if(!isValidCIVDay(civ_tempDay)){
 	               	    
				 	               	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
			 	               	    printf("Error! : This is not a valid Day \n");
			 	               	    SetConsoleTextAttribute(h, 7);  
									return;  
								}
							 
									HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
			                        
			                          // COURSE CLASH IMPLEMENTATION FOR ALL THE COURSES ADDED
								                    
												     if (isClashWithinCIV(
												            civ_tempCourse,
												            civ_tempCourseID,
												            civ_tempHall,
												            civ_tempTime,
												            civ_tempLecturer,
												            civ_tempDay)) {
												        printf("ERROR: Lecturer %s already has a class at %s on %s.\n",
												               civ_tempLecturer, civ_tempTime, civ_tempDay);
												        return;
												    }
				
												     if (isHallOccupiedCIV(civ_tempHall, civ_tempTime, civ_tempDay)) {
												        printf("ERROR: Hall %s is already occupied at %s on %s.\n",
												               civ_tempHall, civ_tempTime, civ_tempDay);
												        return;
												    }
			                        
								                        	strcpy(civ_course[civ_count], civ_tempCourse);
								                        	strcpy(civ_courseID[civ_count], civ_tempCourseID);
															strcpy(civ_time[civ_count], civ_tempTime);
															strcpy(civ_hall[civ_count], civ_tempHall);
															strcpy(civ_lecturer[civ_count], civ_tempLecturer);
															strcpy(civ_day[civ_count], civ_tempDay);
															
												          civ_count ++;  
													
																     saveCIVToCSV(
																	    civ_tempCourse,
																	    civ_tempCourseID,
																	    civ_tempDay,
																	    civ_tempTime,
																	    civ_tempHall,
																	    civ_tempLecturer
																    );
																    
														
								    printf("\nCourse added successfully.\n");
								    
								    SetConsoleTextAttribute(h, 7);
	 }
    
    
     void generateCIVTimeTable(){
 	
 	 
 	     if(civ_count == 0){
 	     	printf("\n No Course added yet.\n");
 	     	return;
		  }
 	 
 	              HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
 	              printf("\n CIV TimeTable\n");
				   
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				  
				  printf("| %-20s | %-8s | %-8s | %-10s | %-8s | %-20s|\n",
	                     "Course","CourseID", "Day", "Time", "Hall", "Lecturer");
	                     
	              printf("+----------------------+----------+------------+----------+----------------------+\n");
 	              
 	              for(i = 0; i < civ_count; i++){
 	              	printf("| %-20s | %-8s | %-8s | %-10s | %-8s | %-20s|\n",
					civ_course[i], civ_courseID[i], civ_day[i], civ_time[i], civ_hall[i], civ_lecturer[i]);
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				   }      
 	               SetConsoleTextAttribute(h, 7);
           }
           
    void  Civil_Engineering(){
	            initCIVCSV();
				int option;
				
				while(1){
					
					printf("\n1. Add course\n2. Generate timetable\n3. Exit\nChoose option: ");
			        scanf("%d", &option);
			        getchar(); 
			        
			        
			        if(option == 1)
			        	addCivCourse();
			        	
					else if(option == 2)
						generateCIVTimeTable();
						
					else if(option == 3)
						break;
				    
				    else 
				       printf("n Ivalide option/choice, select agian");
			}
				
	}
	
	// FOR THE DEPARTMENT OF CHEMICAL AND PETROLEUM ENGINEEING
	
char cpeCourse[][30] = {
 	"Analysis",
 	"Phys for Eng",
 	"programming1",
 };
 

    char cpeTime[][30] = {
        "7-9am",
		"9-11am",
		"11-1pm",
		"1-3pm",
		"3-5pm",
		"5-7pm"
	};
	
	char cpeDay[][30] = {
		"Monday",
		"Tuesday",
		"Wednessday",
		"Thursday",
		"Friday",
		"Saturday"
		
	};
 
    int cpeCourseCount = 3;
    int cpeTimeCount = 6;
    int cpeDayCount = 6;
 
 	char cpe_course[MAX][30];
 	char cpe_courseID[MAX][30];
	char cpe_time[MAX][20];
	char cpe_hall[MAX][20];
	char cpe_lecturer[MAX][20];
	char cpe_day[MAX][15];
	int cpe_count = 0;
	
	
	                int isValidCPECourse(char input[]){
	                	for(i = 0; i < cpeCourseCount; i++){
	                		if(strcmp(input, cpeCourse[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
					  int isValidCPETime(char input[]){
	                	for(i = 0; i < cpeTimeCount; i++){
	                		if(strcmp(input, cpeTime[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
					
					  int isValidCPEDay(char input[]){
	                	for(i = 0; i < cpeDayCount; i++){
	                		if(strcmp(input, cpeDay[i]) == 0){
	                			return 1;
							}
						}
	                	return 0;
					}
 
 							// HERE I AM CHECKING IF COURSES WILL CLASH
	
				int isClashWithinCPE(
				    char newcpe_Course[],
				    char newcpe_Hall[],
				    char newcpe_Time[],
				    char newcpe_Lecturer[],
				    char newcpe_Day[]
				) {
				    for (i = 0; i < cpe_count; i++) {
				        if (strcmp(cpe_lecturer[i], newcpe_Lecturer) == 0 &&
				            strcmp(cpe_time[i], newcpe_Time) == 0 &&
				            strcmp(cpe_day[i], newcpe_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
							
				int isHallOccupiedCPE(char newcpe_Hall[], char newcpe_Time[], char newcpe_Day[]) {
				    for (i = 0; i < cpe_count; i++) {
				        if (strcmp(cpe_hall[i], newcpe_Hall) == 0 &&
				            strcmp(cpe_time[i], newcpe_Time) == 0 &&
				            strcmp(cpe_day[i], newcpe_Day) == 0) {
				            return 1;
				        }
				    }
				    return 0;
				}
					
					
					
					//FOR THE CSV FILE 
			void initCPECSV() {
					    FILE *fp = fopen("CPE_timetable.csv", "r");
					
					    if (fp == NULL) {
					        // File does not exist ? create and add headers
					        fp = fopen("CPE_timetable.csv", "w");
					        if (fp == NULL) {
					            printf("ERROR: Cannot create CSV file.\n");
					            return;
					        }
					
					        fprintf(fp, "Course,CourseID,Day,Time,Hall,Lecturer\n");
					        fclose(fp);
					    } else {
					        fclose(fp);
					    }
					}
					
					void saveCPEToCSV(
					    char cpe_course[],
					    char cpe_courseID[],
					    char cpe_day[],
					    char cpe_time[],
					    char cpe_hall[],
					    char cpe_lecturer[]
					)
					 {
					    FILE *fp = fopen("CPE_timetable.csv", "a");
					
					    if (fp == NULL) {
					        printf("ERROR: Unable to open CSV file.\n");
					        return;
					    }
					
					    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
					            cpe_course, cpe_courseID, cpe_day, cpe_time, cpe_hall, cpe_lecturer);
					
					    fclose(fp);
					}
	
 
 
 
     void addCpeCourse(){
     	char cpe_tempCourse[30];
     	char cpe_tempCourseID[30];
     	char cpe_tempTime[30];
     	char cpe_tempHall[30];
     	char cpe_tempLecturer[30];
     	char cpe_tempDay[30];
     	
			     	        printf("Enter Course Name : ");
			 	            fgets(cpe_tempCourse, 30, stdin);
			 	            cpe_tempCourse[strcspn(cpe_tempCourse, "\n")] = 0;
			 	            
			 	              if(!isValidCPECourse(cpe_tempCourse)){
 	               	    
 	               	            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
		 	               	    printf("Error! : Course Not found in the department of Chemical and Petroleum Engineering \n");
		 	               	    return;
		 	               	    SetConsoleTextAttribute(h, 7);    
					}
					           
					           
					        printf("Enter Course ID : ");
			 	            fgets(cpe_tempCourseID, 30, stdin);
			 	            cpe_tempCourseID[strcspn(cpe_tempCourseID, "\n")] = 0;
				 
							 printf("Enter Time : ");
							 fgets(cpe_tempTime, 30, stdin);
							 cpe_tempTime[strcspn(cpe_tempTime, "\n")] = 0;
							 
							     if(!isValidCPETime(cpe_tempTime)){
 	               	    
					 	               	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
				 	               	    printf("Error! : This is not a valid School Hour \n");
				 	               	    SetConsoleTextAttribute(h, 7); 
										return;    
								}
							 
							 printf("Enter Hall : ");
							 fgets(cpe_tempHall, 30, stdin);
							 cpe_tempHall[strcspn(cpe_tempHall, "\n")] = 0;
							 
							 printf("Enter Lecturer Name : ");
							 fgets(cpe_tempLecturer, 20, stdin);
							 cpe_tempLecturer[strcspn(cpe_tempLecturer, "\n")] = 0;
							 
							 printf("Enter Day : ");
							 fgets(cpe_tempDay, 30, stdin);
							 cpe_tempDay[strcspn(cpe_tempDay, "\n")] = 0;
							 
							     if(!isValidCPEDay(cpe_tempDay)){
 	               	    
					 	               	    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			                                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
					 	               	    printf("Error! : This is not a valid Day \n");
					 	               	    SetConsoleTextAttribute(h, 7);
											return;    
									}
									
									
									   // COURSE CLASH IMPLEMENTATION FOR ALL THE COURSES ADDED
								                    
												     if (isClashWithinCPE(
												            cpe_tempCourse,
												            cpe_tempHall,
												            cpe_tempTime,
												            cpe_tempLecturer,
												            cpe_tempDay)) {
												        printf("ERROR: Lecturer %s already has a class at %s on %s.\n",
												               cpe_tempLecturer, cpe_tempTime, cpe_tempDay);
												        return;
												    }
				
												     if (isHallOccupiedCPE(cpe_tempHall, cpe_tempTime, cpe_tempDay)) {
												        printf("ERROR: Hall %s is already occupied at %s on %s.\n",
												               cpe_tempHall, cpe_tempTime, cpe_tempDay);
												        return;
												    }
			                                          
			                                          
							 
															HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
									                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
										
										
										                    strcpy(cpe_course[cpe_count], cpe_tempCourse);
															strcpy(cpe_time[cpe_count], cpe_tempTime);
															strcpy(cpe_hall[cpe_count], cpe_tempHall);
															strcpy(cpe_lecturer[cpe_count], cpe_tempLecturer);
															strcpy(cpe_day[cpe_count], cpe_tempDay); 
				                        
									                        cpe_count++;
									    
									                                saveCPEToCSV(
																	    cpe_tempCourse,
																	    cpe_tempCourseID,
																	    cpe_tempDay,
																	    cpe_tempTime,
																	    cpe_tempHall,
																	    cpe_tempLecturer
																    );
									    printf("\nCourse added successfully.\n");
									    
									    SetConsoleTextAttribute(h, 7);
	 }
    
    
void generateCpeTimeTable(){
 	
 	 
 	     if(cpe_count == 0){
 	     	printf("\n No Course added yet.");
 	     	return;
		  }
 	 
 	              HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
 	              printf("\n CPE TimeTable\n");
				   
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				  
				  printf("| %-20s | %-8s | %-8s | %-10s | %-8s | %-20s |\n",
	                     "Course", "CourseID", "Day", "Time", "Hall", "Lecturer");
	                     
	              printf("+----------------------+----------+------------+----------+----------------------+\n");
 	              
 	              for(i = 0; i < cpe_count; i++){
 	              	printf("| %-20s | %-8 | %-8s | %-10s | %-8s | %-20s |\n",
					       cpe_course[i],  cpe_courseID[i], cpe_day[i], cpe_time[i], cpe_hall[i], cpe_lecturer[i]);
					       
				  printf("+----------------------+----------+------------+----------+----------------------+\n");
				   }      
 	                SetConsoleTextAttribute(h, 7);
           }
           
    void Chemical_Petroleum_Engineering(){
	            initCPECSV();
				int option;
				
				while(1){
					
					printf("\n1. Add course\n2. Generate timetable\n3. Exit\nChoose option: ");
			        scanf("%d", &option);
			        getchar(); 
			        
			        
			        if(option == 1)
			        	addCpeCourse();
			        	
					else if(option == 2)
						generateCpeTimeTable();
						
					else if(option == 3)
						break;
				    
				    else 
				       printf("n Ivalide option/choice, select agian");
			}
				
	}
	
	
	// MAIN PROGRAM ITSELF
	int main(){
		
    int choice;
    
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    while (1) {
        printf(" ================================================\n");
        printf("|          FET AUTO-GENERATIVE TIMETABLE SYSTEM  |\n");
        printf(" ================================================\n");
        SetConsoleTextAttribute(h, 7);
        printf("\n");
        printf("\n");
        printf("1. Computer Engineering (CE)\n");
        printf("2. Electrical Engineering (EE)\n");
        printf("3. Civil Engineering (CIV)\n");
        printf("4. Mechanical Engineering (ME)\n");
        printf("5. Chemical and Petroleum Engineering (CPE)\n");
        printf("6. Exit\n");
        printf("Choose department: ");
    

        scanf("%d", &choice);
        getchar(); 
		  // clear newline from buffer

        if (choice == 1)
            Computer_Engieering () ;          // CE
        else if (choice == 2)
            Electrical_Engineering();        // EE
        else if (choice == 3)
            Civil_Engineering();             // CIV
        else if (choice == 4)
             Mechanical_Engineering();        // ME
        else if (choice == 5)
            Chemical_Petroleum_Engineering();   // CPE
        else if (choice == 6) {
            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
