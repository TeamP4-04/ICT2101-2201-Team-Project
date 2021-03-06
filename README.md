# ICT2101-2201-Team-Project
This repository aims to deliver the project requirements in SIT ICT Module 2101/2104. 

## How to run

### To run the application on VSCode:
1. Create a virtual environment  
 ```python -m venv venv```  
```venv\Scripts\activate```  
2. Install the dependencies  
```python3 -m pip install -r requirements.txt```  
- In case you encounter this conflicting error 'can't find Rust Compiler':
![image](https://user-images.githubusercontent.com/71871190/143470692-27069d67-bf2f-4958-9b6f-634e6b858230.png)  
Run ```python -m pip install --upgrade pip```  

### To run in command line:
3. In the directory where webportal.py is located, open a cmd interface.  
4. Enter the following commands followed by flask run will start the server.  
```set FLASK_APP=webportal.py```  
```set FLASK_DEBUG=1``` where debug = 1 is to make it so that it updates the pages.  
```python ./webportal.py``` 

![image](https://user-images.githubusercontent.com/71871190/143473789-51f2f610-b12a-4014-9021-a1ab6f4af49b.png)  
5. Click on the ip address ```http://127.0.0.1:5000/``` to visit the web portal.  

## Development Workflow
The Git Feature Workflow with Development Branch is used by the team. We have a Development Branch that runs alongside the Master Branch and reflects the most recent development changes for the next release. Then, from the Development Branch, each developer on the team creates their own Feature Branch to work on the web portal's assigned features.  
Once a feature has been tested, it is merged with the Development Branch before being merged with the Master Branch.  

### Project set up steps:
1. Clone project  
```git clone https://github.com/TeamP4-04/ICT2101-2201-Team-Project.git```

2. Checkout dev branch  
```git checkout dev```

3. Create and checkout feature branch  
```git checkout -b feature/<featurename>```

4. Push your feature branch to GitHub  
```git push -u origin feature/<featurename>```

### Basic workflow:
1. Checkout your feature branch  
```git checkout feature/<featurename>```

1. Code and test your feature  

2. Add your changes to the feature branch (best practice to add the files that you modified only)  
```git add <file name>```

4. Commit your changes  
```git commit -m “<commit message>”```  
or  
```git commit``` Press enter and type the summary and description for the commit. Then press esc and type :wq  

5. Push your changes to Github  
```git push```

### Get updates from master branch to your own branch:
1. Check out master branch  
```git checkout master```

2. Pull updates from remote master branch to local master branch    
```git pull```

3. Change back to feature branch  
```git checkout feature/<featurename>```

4. Merge master branch code to feature branch  
```git merge master```

### Once the feature is completed, merge it to dev branch then to master branch:  
You can create a pull request in Github to merge your branch to master branch  

#### OR
1. Checkout dev branch  
```git checkout master```  

2. Merge your feature branch to dev branch  
```git merge feature/<featurename>```  

3. Once every feature is integrated and tested, then it is ready to merge into master branch.  
4. Checkout master branch  
```git checkout master```  

- Merge dev branch to master branch  
```git merge dev```

5. Delete local feature branch   
```git branch -d feature/<featurename>```  

6. Delete remote feature branch  
```git push origin --delete feature/<featurename>```  

**Note: Best practice to commit your changes regularly**

## User Acceptance Testing

### Use Case Diagram  
![image](https://user-images.githubusercontent.com/71871190/144734776-ac2b5401-ccee-4534-8570-992871c051a2.png)  

### System State Diagram  
![image](https://user-images.githubusercontent.com/71871190/144734786-3b748a4b-1544-43e6-b8b9-58ec4a2b57c0.png)  

### User Acceptance Testing Video 
[![UAT Video](http://img.youtube.com/vi/3BZyPw8U0CA/0.jpg)](http://www.youtube.com/watch?v=3BZyPw8U0CA "UAT video") 

Alternatively, you can click on this link to watch the video https://www.youtube.com/watch?v=3BZyPw8U0CA


## Whitebox Testing

### One Meaningful Class 
  We have decided to choose Tutorial.

### Test Suite
The following python scripts below are test cases for the test suite:
1. test_path1.py [test_loadTutorialdetails()] (**Baseline**)
2. test_path2.py [test_checkLastTutID()]
3. test_path3.py [test_existsTutorialID()]
4. test_path4.py [test_databaseconnection()]
5. test_path5.py [test_loadAllTutID()]
  
They reside in the ```RoboCarWEBPORTAL folder```  of the repo.  


### Code Coverage Statistics
    Path Coverage was conducted on the Tutorial Class where V(G) = e - n + 2(p) such that:
    - Edges = 18
    - Nodes = 17
    - Components = 2
    Hence a minimum of 5 paths are needed to have sufficient coverage.  
    We have generated these statistics manually.

![image](https://user-images.githubusercontent.com/71871190/144795438-f22a3d2f-b3c8-477b-96fb-7cf3d4df5865.png)  

![image](https://user-images.githubusercontent.com/71871190/144795407-ca3fa431-9b9e-41ef-902b-aa315a0443e8.png)  

![image](https://user-images.githubusercontent.com/71871190/144795475-8e93c8a6-c179-4780-a6fa-604f620a01c1.png)  


### Instructions on how to run the Test Suite
    1. Ensure that Pytest is installed.
    2. Ensure test scripts are in the same directory as webportal.py.
    3. Open a command prompt from the same directory.
    4. Enter "pytest" into the command prompt to run all test scripts.
    
#### Test Suite Video    
https://user-images.githubusercontent.com/72189764/144799492-23099a29-fa44-4648-9460-802cdf0a5170.mp4

    
## Individual Reflections  
Please go to the ```M3 Individual Reflection Folder``` to access our individual reflections.
