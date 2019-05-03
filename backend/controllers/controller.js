/******************************************************************************************^^****
*                                                                                               *
*     COMPUTER SCIENCE 142 PROJECT: N-CHANCELLORS MOVE SOLVER                                   *
*                                                                                               *
*     PURPOSE                                                                                   *
*     This controller contains all algorithms used in the program.                              *                                                                            *
*                                                                                               *
*     USAGE                                                                                     *
*     Import this file to any javascript program to be able to call the methods present.        *                     *
*                                                                                               *
*     SUBROUTINES AND FUNCTION SUBPROGRAMS REQUIRED                                             *
*     None.                                                                                     *
*                                                                                               *
*     METHOD                                                                                    *
*     The program contains the following methods:                                               *                                                                              *
*                                                                                               *
*     PROGRAMMERS                                                                               *
*     BATICOS, Andric Quinn                                                                     *
*     NICOLAS, Mark Jay                                                                         *
*     REBLORA, Kyle Matthew                                                                     *
*                                                                                               *
*     DATE-WRITTEN                                                                              *
*     April 2019                                                                                *
*                                                                                               *
****************************************************************************************^^******/
'use strict';

exports.findSolution = (req, res, next) => {

	var string = req.query.string;
	
	function start() {
		return res.status(200).send("OK");
	}

  start();
}