#Parent class
class tutorial:
    def __init__(self, tutorialName, tutorialOverview, tutorialVideo, tutorialID):
        self.__tutorialID = tutorialID
        self.__tutorialName = tutorialName
        self.__tutorialOverview = tutorialOverview
        self.__tutorialVideo = tutorialVideo

    # Getter and Setter Methods
    def get_tutorialID(self):
        return self.__trolley
    def set_tutorialID(self, tutorialID):
        self.__tutorialID = tutorialID
    def get_tutorialName(self):
        return self.__tutorialName
    def get_tutorialOverview(self):
        return self.__tutorialOverview
    def get_tutorialVideo(self):
        return self.__tutorialVideo
    