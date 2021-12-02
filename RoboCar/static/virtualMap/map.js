class GridSystem {
    constructor(matrix, playerX, playerY) {
        // referencing the matrix everytime
        this.matrix = matrix; 
        // this.uiContext = this.#getContext(420, 580, "#333333");
        this.outlineContext = this.#getContext(0,0, "#757575");
        this.topContext = this.#getContext(0,0, "#F5F5F5", true);
        this.cellSize = 35;
        this.padding = 4;

        // Create player (Car) object & set the matrix position
        this.player = { x: playerX, y: playerY, color: "red"};
        this.matrix[playerX][playerY] = 2;

        document.addEventListener("keydown", this.movePlayer);
    }

    /**
	 * Check if the move is valid
	 * @param {number} x - column of grid
	 * @param {number} y - row of grid
     * @return {boolean} - true or false for the validity of move  
	 */
	#isValidMove(x, y) {
		if (this.matrix[this.player.y + y][this.player.x + x] === 0) {
			return true;
		}
		return false;
	}

    /**
	 * Updates the matrix of the map
	 * @param {number} y - row of grid to clear
	 * @param {number} x - column of grid to clear
	 * @param {number} val - Value of the matrix to update
     * @return {void}
	 */
	#updateMatrix(y, x, val) {
		this.matrix[y][x] = val;
	}

    /**
     * Move the player based on keystrokes
     * @param {number} keycode - keystokes from keyboard
     * @return {void}
     */
    movePlayer = ( { keyCode } ) => {
        console.log("Moving the car");
        if (keyCode === 37) { // left
            if (this.#isValidMove(-1, 0)) {
                // Clear the current postition of player
                this.matrix[this.player.y][this.player.x] = 0;
                this.#updateMatrix(this.player.y, this.player.x, 0);
                // Set the new position of player
                this.#updateMatrix(this.player.y, this.player.x - 1, 2);
                this.player.x --;
                this.render();
            }

        } else if (keyCode === 39) { // right
            if (this.#isValidMove(1, 0)) {
                this.#updateMatrix(this.player.y, this.player.x, 0);
 			 	this.#updateMatrix(this.player.y, this.player.x + 1, 2);
                this.player.x ++;
                this.render();
            }

        } else if (keyCode === 38) { // up
            if (this.#isValidMove(0, -1)) {
                this.#updateMatrix(this.player.y, this.player.x, 0);
 			 	this.#updateMatrix(this.player.y - 1, this.player.x, 2);
                this.player.y --;
                this.render();
            }
        } else if (keyCode === 40) { // down
            if (this.#isValidMove(0, 1)) {
                this.#updateMatrix(this.player.y, this.player.x, 0);
 			 	this.#updateMatrix(this.player.y + 1, this.player.x, 2);
                this.player.y ++;
                this.render();
            }
        }
    }

    // /**
    //  * Position the grid to center
    //  * @param {number} w - Width of the area
    //  * @param {number} h - Height of the area
    //  * @return {number} - The x and y values of the area
    //  */
    // #getCenter(w, h) {
    //     return {
    //         x:  window.innerWidth / 2 - w / 2 + "px",
    //         y:  window.innerHeight / 2 - h / 2 + "px"
    //     };
    // }


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
        this.canvas.style.marginLeft = "60px";
        this.canvas.style.marginTop = "20px";
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

		// const center = this.#getCenter(w, h);
		// this.outlineContext.canvas.style.marginLeft = center.x
		// this.outlineContext.canvas.style.marginTop = center.y;

		// this.topContext.canvas.style.marginLeft = center.x
		// this.topContext.canvas.style.marginTop = center.y;

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

				this.outlineContext.fillStyle = color;
				this.outlineContext.fillRect(col * (this.cellSize + this.padding),
				row * (this.cellSize + this.padding),
				this.cellSize, this.cellSize);
			}
		}

        // // Set title of the virtual map
		// this.uiContext.font = "20px Courier";
		// this.uiContext.fillStyle = "white";
		// this.uiContext.fillText("Virtual Map", 20, 30);
	}
}

// 8 * 8 Grid Matrix
const gridMatrix = [
	[0, 0, 0, 1, 0, 0, 0, 0],
	[0, 0, 0, 1, 0, 0, 0, 0],
	[0, 1, 1, 1, 0, 1, 1, 0],
	[0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0]
];

/**
 * Create a GridSystem object
 * @param gridMatrix array - Width of the area
 */

// Set the x, y positions of the player (1,1)
const gridSystem = new GridSystem(gridMatrix, 0, 0);  
gridSystem.render();
