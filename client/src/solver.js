export const solver = (file) => {
    // console.log(file);

    let filecontent = file.split('\n');

    // create a copy of the content of the files
    let lines = filecontent.slice();
    
    let numOfBoards = parseInt(lines[0]);
    
    // remove the first element in lines array
    lines.shift();
    let solution = []
    
    for (let i=0; i < numOfBoards; i++) {
        
        let n = parseInt(lines[0]);
        lines.shift();

        // Chancellors Creation
        let chancellorStack = [];
        let chancellorC = 0;


        let stringifiedMatrix = ''
        for (let j=0; j<n; j++) {

            // remove the \n from each line
            stringifiedMatrix += (lines[j].substring(0, n));
        }

        for (let j=0; j<n; j++) {
            lines.shift();
        }        


        // Matrix Creation
        let size = n*n
        let board = []

        
        for (let j=0; j<stringifiedMatrix.length; j++) {
            let currentChar = stringifiedMatrix[j]
            
            board.push(currentChar);
            
            if (currentChar === 'C') chancellorStack[chancellorC++] = j
        }


        let hasNoSolution = 0, numberOfErrors = 0;

        for (let m=0; m<chancellorC; m++) {
            for (let k=m; k<chancellorC; k++) {
                if (m!==k) {
                    let x = parseInt(chancellorStack[m] / n);
                    let y = parseInt(chancellorStack[m] % n);
                    let a = parseInt(chancellorStack[k] % n);
                    let b = parseInt(chancellorStack[k] % n);
                    
                    if (a === x || b === y || (Math.abs(x-a) === 2 && Math.abs(y-b) === 1) || (Math.abs(x-a) === 1 && Math.abs(y-b) === 2) ) {
                        hasNoSolution = 1;
                        numberOfErrors++;
                    }
                }
            }
        }

        
        let solutions = 0;

        if (hasNoSolution === 0) {
            let start, move;
            let nopts = [];
            let options = [...Array(n+2-chancellorC)].map(e => Array(size+2-chancellorC));
            let i, candidate;

            move = start = 0;
            nopts[start] = 1;


            while (nopts[start] > 0) {
                if (nopts[move] > 0) {
                    move++;
                    nopts[move] = 0;

                    // SOLUTION FOUND!

                    if (move === n+1-chancellorC) {
                        solutions++

                        let tempSolution = []
                        // let count = 0;
                        for (let i=0; i<chancellorC; i++){
							tempSolution.push(chancellorStack[i]);
							// count++;
						}

                        for(let i=1; i<move;i++) {
                            tempSolution.push(options[i][nopts[i]]);
                            // count++
							// console.log(options[i][nopts[i]]);
                        }

                        // console.log('\n');
                        // console.log(solutions);
                        // console.log('\n\n');
                        solution.push(tempSolution)
                        

                    } 
                    else if (move === 1) {
                        for (candidate=size-1; candidate >= 0; candidate--) {
                            let x = parseInt(candidate / n);
                            let y = parseInt(candidate % n);
                            let isValid = 1;

                            for (let i = 0; i < chancellorC; i++) {
                                let a = parseInt(chancellorStack[i] / n);
                                let b = parseInt(chancellorStack[i] % n);

                                if (a === x || b === y || (Math.abs(x-a) === 2 
                                && Math.abs(y-b) === 1) || (Math.abs(x-a) === 1 
                                && Math.abs(y-b) === 2)) isValid = 0;
                                
                            }

                            if (isValid === 1) {
                                nopts[move]++;
                                options[move][nopts[move]] = candidate;
                            }
                        }
                    }
                    else {
                        for (candidate=1; candidate <= nopts[move-1]; candidate++) {
                            let topOfStack = options[move-1][nopts[move-1]];

                            let x = parseInt(topOfStack / n);
                            let y = parseInt(topOfStack % n);

                            let current = options[move-1][candidate];

                            let a = parseInt(current / n);
                            let b = parseInt(current % n);

                            // Rook / Knight Move Checking

                            if (!(a===x || b===y || (Math.abs(x-a) === 2 && Math.abs(y-b) === 1) || (Math.abs(x-a) === 1 && Math.abs(y-b)=== 2))) {
                                nopts[move]++;
                                options[move][nopts[move]] = current;
                            }
                        }
                    }
                }
                else {
                    move--;
                    nopts[move]--;
                }
            }            
        }
        
        console.log(solution);
        console.log("No. of solutions found: " + solution.length);

        return {
            solution
        }
    }
    
}