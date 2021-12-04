class GridSystem {
    constructor(matrix, playerX, playerY) {
        this.matrix = matrix; 
        this.outlineContext = this.#getContext(0,0, "#757575");
        this.topContext = this.#getContext(0,0, "#F5F5F5", true);
        this.cellSize = 70;
        this.padding = 4;

        // Create player (Car) object & set the matrix position
        this.player = { x: playerX, y: playerY, color: "red"};
        this.matrix[playerX][playerY] = 2;
		this.end = { x: playerX, y: playerY, color: "green"};
    }
	
	
	/* --- EXECUTE CAR MOVEMENT WITH BLOCKLY COMMANDS --- */
	moveUp(){
		if (gridSystem.#isValidMove(0, -1)) {
                gridSystem.#updateMatrix(gridSystem.player.y, gridSystem.player.x, 0);
 			 	gridSystem.#updateMatrix(gridSystem.player.y - 1, gridSystem.player.x, 2);
                gridSystem.player.y --;
				gridSystem.render();
        }
		else{
			gridSystem.render();
			setTimeout(function(){ alert("You failed to get to the End Point!"); }, 500);
			setTimeout(function(){ gridSystem.#reset(); }, 1000);
		}
		
	}
	
	moveDown(){
		if (gridSystem.#isValidMove(0, 1)) {
                gridSystem.#updateMatrix(gridSystem.player.y, gridSystem.player.x, 0);
 			 	gridSystem.#updateMatrix(gridSystem.player.y + 1, gridSystem.player.x, 2);
                gridSystem.player.y ++;
                gridSystem.render();
        }
		else{
			gridSystem.render();
			setTimeout(function(){ alert("You failed to get to the End Point!"); }, 500);
			setTimeout(function(){ gridSystem.#reset(); }, 1000);
		}
	}
	
	moveLeft(){
		if (gridSystem.#isValidMove(-1, 0)) {
                // Clear the current postition of player
                gridSystem.matrix[gridSystem.player.y][gridSystem.player.x] = 0;
                gridSystem.#updateMatrix(gridSystem.player.y, gridSystem.player.x, 0);
                // Set the new position of player
                gridSystem.#updateMatrix(gridSystem.player.y, gridSystem.player.x - 1, 2);
                gridSystem.player.x --;
                gridSystem.render();
        }
		else{
			gridSystem.render();
			setTimeout(function(){ alert("You failed to get to the End Point!"); }, 500);
			setTimeout(function(){ gridSystem.#reset(); }, 1000);
		}
	}
	
	moveRight(){
		if (gridSystem.#isValidMove(1, 0)) {
                gridSystem.#updateMatrix(gridSystem.player.y, gridSystem.player.x, 0);
 			 	gridSystem.#updateMatrix(gridSystem.player.y, gridSystem.player.x + 1, 2);
                gridSystem.player.x ++;
                gridSystem.render();
        }
		else{
			gridSystem.render();
			setTimeout(function(){ alert("You failed to get to the End Point!"); }, 500);
			setTimeout(function(){ gridSystem.#reset(); }, 1000);
		}
	}
	
	/* --- END OF CAR MOVEMENT BLOCKLY COMMANDS --- */

	#isValidMove(x, y) {
		if (this.matrix[this.player.y + y][this.player.x + x] === 0) {
			
			return true;
		}
		else if(this.matrix[this.player.y + y][this.player.x + x] === 3){
			setTimeout(function(){ alert("You win!"); }, 500);
			setTimeout(function(){ gridSystem.#reset(); }, 1000);
			return true;
		}
		return false;
	}


	#updateMatrix(y, x, val) {
		this.matrix[y][x] = val;
	}

	/* --- RESET GAME --- */
	#reset(){
		if(confirm('Reset Game?')){
			window.location.replace("/dashboard");
		}
		else{
			return false;
		}
	}
	/* --- END OF RESET GAME --- */


    /**
     * Create canvas and setting the style of the grid
     * @param {number} w - Width of the area
     * @param {number} h - Height of the area
     * @param {string} color - Height of the area
     * @param {boolean} isTransparent - Determine the canvas to be transparent or not
     */
    #getContext(w, h, color = "#F5F5F5", isTransparent = false) {
        this.canvas = document.createElement("canvas");
        this.context = this.canvas.getContext("2d"); // get context to draw things
        this.width = this.canvas.width = w;
        this.height = this.canvas.height = h;
        this.canvas.style.position = "absolute";
        this.canvas.style.background = color;

        //
        if (isTransparent) {
            this.canvas.style.backgroundColor = "transparent";
        }

        // const center = this.#getCenter(w, h);
        this.canvas.style.marginLeft = "80px";
        this.canvas.style.marginTop = "30px";
        document.getElementById("virtualMap").append(this.canvas);

        return this.context;
    }

    /**
     * Render the grid
     * @param {number} w - Width of the area
     * @param {number} h - Height of the area
     * @param {string} color - color of grid
     * @param {boolean} isTransparent - Determine the canvas to be transparent or not
     */
     render() {
		const w = (this.cellSize + this.padding) * this.matrix[0].length - (this.padding);
		const h = (this.cellSize + this.padding) * this.matrix.length - (this.padding);

		this.outlineContext.canvas.width = w;
		this.outlineContext.canvas.height = h;


		for (let row = 0; row < this.matrix.length; row ++) {
			for (let col = 0; col < this.matrix[row].length; col ++) {
				const cellVal = this.matrix[row][col];
				let color = "#F5F5F5";

                // Set color for cell if it is an obstacle
				if (cellVal === 1) {
					color = "#4488FF";
				} 
                else if (cellVal === 2) {
                    // Set color of player
					color = this.player.color;
				}
				else if (cellVal === 3) {
                    // Set color of Endpoint
					color = this.end.color;
				}


				this.outlineContext.fillStyle = color;
				this.outlineContext.fillRect(col * (this.cellSize + this.padding),
				row * (this.cellSize + this.padding),
				this.cellSize, this.cellSize);
			}
		}
	}
}

// 8 * 8 Grid Matrix
//const gridMatrix = [
//	[0, 0, 0, 1, 0, 0, 0, 0],
//	[0, 0, 0, 1, 0, 0, 0, 0],
//	[0, 1, 1, 1, 0, 1, 1, 0],
//	[0, 0, 0, 0, 0, 0, 0, 0],
//	[0, 0, 0, 0, 0, 0, 0, 0],
//  [1, 1, 0, 0, 0, 0, 0, 0],
//  [0, 0, 0, 0, 0, 0, 0, 0],
//	[0, 0, 0, 0, 0, 0, 0, 0]
//];

// 4 * 4 Grid Matrix
const gridMatrix = [
	[0, 0, 1, 1],
	[1, 0, 0, 0],
	[3, 1, 1, 0],
	[0, 0, 0, 0]
];

/**
 * Create a GridSystem object
 * @param gridMatrix array - Width of the area
 */

// Set the x, y positions of the player (1,1)
const gridSystem = new GridSystem(gridMatrix, 0, 0);  
gridSystem.render();