# ICT2101-2201-Team-Project
This repository aims to deliver the project requirements in SIT ICT Module 2101/2104. 

## How to run

- keep it straight to the point of how to access the entry point of the web app
any necessary dependencies to run it

### To run the application on VSCode:
1. Create a virtual environment```
```python -m venv venv```
```venv\Scripts\activate```
2. Install the dependencies
```python3 -m pip install -r requirements.txt```
- In case you encounter this conflicting error 'can't find Rust Compiler':
![image](https://user-images.githubusercontent.com/71871190/143470692-27069d67-bf2f-4958-9b6f-634e6b858230.png)
- Enter```python -m pip install --upgrade pip```

### To run command line
3. In the directory where webportal.py is located, open a cmd interface.
4. Enter the following commands followed by flask run will start the server
```set FLASK_APP=webportal.py```
```set FLASK_DEBUG=1``` where debug = 1 is to make it so that it updates the pages.
```python ./webportal.py``` 
![image](https://user-images.githubusercontent.com/71871190/143473789-51f2f610-b12a-4014-9021-a1ab6f4af49b.png)
5. Click on the ip address ```http://127.0.0.1:5000/``` to visit the web portal.

## Development Workflow
The team uses the Git Feature Workflow with Development Branch. We have a Development Branch that is in parallel to the Master Branch such that it reflects the current development changes for the next release. From there, each developer on the team creates their own Feature Branch from the Development Branch to work on their assigned features of the web portal. Once a feature is tested, the feature branch is merged with the Development Branch before finally merging with the Master Branch.

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

### Once the feature is completed, merge it to master branch:  
You can create a pull request in Github to merge your branch to master branch  

#### OR
1. Checkout master branch  
```git checkout master```  

2. Merge your feature branch to master branch  
```git merge feature/<featurename>```  

3. Delete local feature branch   
```git branch -d feature/<featurename>```  

4. Delete remote feature branch  
```git push origin --delete feature/<featurename>```  

**Note: Best practice to commit your changes regularly**

## User Acceptance Testing

- include an updated use case diagram and system state diagram if there are changes made based on M2. Highlight the changes clearly.
an embedded video that runs through all the system test cases you have created (and refined) from M2
~3 mins long to cover all system tests

## Whitebox Testing

- choose one meaningful class to demonstrate your test code. “Meaningful” here means 2 or more interactions with other classes, e.g., a Control class. Please do not use an Entity class.
- list the test cases for this test suite (for this one class) and where they reside in your repo
- show code coverage statistics for each test case, including an explanation of how you have generated these statistics (whether manual, through a lib, or via the IDE)
- provide instructions how to run the test suite
- embed an animated gif or another short video (~1 min) of the test case being ran