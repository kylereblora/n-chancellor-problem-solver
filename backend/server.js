/**********************************************************************************************
*                                                                                             *
*     COMPUTER SCIENCE 142 PROJECT: N-CHANCELLORS MOVE SOLVER                                 *
*                                                                                             *
*     PURPOSE                                                                                 *
*     This server shall perform the algorithm to solve the n-chancellors problem,             *
*     by receiving input from this machine and this machine only.                             *
*                                                                                             *
*     USAGE                                                                                   *
*     Run nodemon server.js                                                                   *
*                                                                                             *
*     SUBROUTINES AND FUNCTION SUBPROGRAMS REQUIRED                                           *
*     This file requires a router file that shall handle all the controllers used in this     *
*     program.                                                                                *
*                                                                                             *
*     METHOD                                                                                  *
*     The program creates an express application, sets all the necessary libraries and        *
*     settings used, and exports the created application.                                     *
*                                                                                             *
*     PROGRAMMERS                                                                             *
*     BATICOS, Andric Quinn                                                                   *
*     NICOLAS, Mark Jay                                                                       *
*     REBLORA, Kyle Matthew                                                                   *
*                                                                                             *
*     DATE-WRITTEN                                                                            *
*     April 2019                                                                              *
*                                                                                             *
**********************************************************************************************/
'use strict';
const express = require('express');
const port = process.env.PORT || 3001;
const router = require(__dirname + '/routes/router');

let app;
let handler;
let start;

start = () => {

  if (handler) {
    handler.close();
  }

  //  create express application
  app = express();

  //  set environment for express
  app.set('case sensitive routing', true);
  app.disable('x-powered-by');

  router(app);
  return app.listen(port, () => {
    console.log(`[SUCCESS] Server started. Listening on port ${port}`);
  });

}

handler = start();

module.exports = {
  app,
  handler
}