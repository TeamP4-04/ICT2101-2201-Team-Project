#Parent class
class logs:
    def __init__(self, logID, stageID, commands):
        self.__logID = logID
        self.__stageID = stageID
        self.__commands = commands
       
    # Getter and Setter Methods
    def get_logID(self):
        return self.__logID
    def set_logID(self, logID):
        self.__logID = logID
    def get_stageID(self):
        return self.__stageID
    def get_commands(self):
        return self.__commands
    