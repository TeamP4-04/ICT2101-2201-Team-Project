
/* --- Move Up --- */
Blockly.Blocks['moveup'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Move Up");
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(260);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.JavaScript['moveup'] = function(block) {
	gridSystem.moveUp();
	return 'w';
};

/* --- Move Down --- */
Blockly.Blocks['movedown'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Move Down");
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(260);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.JavaScript['movedown'] = function(block) {
	gridSystem.moveDown();
	return 'r';
};

/* --- Move Left --- */
Blockly.Blocks['moveleft'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Move Left");
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(260);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.JavaScript['moveleft'] = function(block) {
	gridSystem.moveLeft();
	// return 'moveLeft()\n';
  return 'a';
};

/* --- Move Right --- */
Blockly.Blocks['moveright'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Move Right");
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(260);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.JavaScript['moveright'] = function(block) {
	gridSystem.moveRight();
	// return 'moveRight()\n';
  return 'd';
};

/* --- Set Speed --- */
Blockly.Blocks['setspeed'] = {
  init: function() {
    this.appendValueInput("speed")
        .setCheck("Number")
        .appendField("Set Speed (cm/s)");
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(65);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['setspeed'] = function(block) {
  var value_speed = Blockly.JavaScript.valueToCode(block, 'speed', Blockly.JavaScript.ORDER_ATOMIC);
  var value = 'Speed = ' + value_speed + '\n';
  return value;
};