/*
=============================================
REQUIRES
=============================================
*/

const fs = require('fs');
const execSync = require('child_process').execSync;
const out_general_optimizations = fs.openSync('./results_general_optimizations.csv', 'a');
const out_particular_optimizations = fs.openSync('./results_particular_optimizations.csv', 'a');
const out_general_base = fs.openSync('./results_general_base.csv', 'a');
const out_particular_base = fs.openSync('./results_particular_base.csv', 'a');
/*
=============================================
BASES
=============================================
*/

const DIRECTORY_BIN_BASE = '../../bin/base';
const base_geral = 'general';
const base_particular = 'particular';

/*
=============================================
OTIMIZATIONS
=============================================
*/

const DIRECTORY_BIN_OPT = '../../bin/optimization';
const opt_generals = [
  'general_fastcmp',
  'general_heuristic',
  'general_heuristic_fastcmp',
  'general_heuristic_sort1',
  'general_heuristic_sort1_fastcmp',
  'general_heuristic_sort2',
  'general_heuristic_sort2_fastcmp',
  'general_heuristic_sort3',
  'general_heuristic_sort3_fastcmp',
];
const opt_particulars = [
  'particular_fastcmp',
  'particular_iterative',
  'particular_iterative_fastcmp',
  'particular_iterative_memlinear',
  'particular_iterative_memlinear_fastcmp',
];

/*
=============================================
TESTS CASES
=============================================
*/

const DIRECTORY_TEST_GENERAL    = '../../tests_case/general';
const DIRECTORY_TEST_PARTICULAR = '../../tests_case/particular';

let tests_cases = [
  '1_10.in',
  '1_3.in',
  '1_6.in',
  '1_9.in',
  '3_1.in',
  '3_4.in',
  '3_7.in',
  '4_10.in',
  '4_3.in',
  '4_6.in',
  '4_9.in',
  '1_1.in',
  '1_4.in',
  '1_7.in',
  '3_2.in',
  '3_5.in',
  '3_8.in',
  '4_1.in',
  '4_4.in',
  '4_7.in',
  '1_2.in',
  '1_5.in',
  '1_8.in',
  '3_10.in',
  '3_3.in',
  '3_6.in',
  '3_9.in',
  '4_2.in',
  '4_5.in',
  '4_8.in'
];

tests_cases.sort()

/*
=============================================
RUNS
=============================================
*/

function opt_gerals_run() {
  let time1, time2;
  opt_generals.forEach((file_general)=> {
    tests_cases.forEach((test_case)=> {
      try {
        let time_tot = 0;
        for(let i = 0; i < 50; i++) {
          let time1 = new Date().getTime();
          execSync(`./${DIRECTORY_BIN_OPT}/${file_general} < ${DIRECTORY_TEST_GENERAL}/${test_case}`);
          let time2 = new Date().getTime();
          time_tot += (time2 - time1);
        }
        fs.writeFile(out_general_optimizations, `${file_general};${test_case};${time_tot/50.0}\n`);
      } catch(err) {
        console.log(err)
      }
    })
  })
}

function opt_particulars_run() {
  let time1, time2;
  opt_particulars.forEach((file_particular)=> {
    tests_cases.forEach((test_case)=> {
      try {
        let time_tot = 0;
        for(let i = 0; i < 50; i++) {
          let time1 = new Date().getTime();
          execSync(`./${DIRECTORY_BIN_OPT}/${file_particular} < ${DIRECTORY_TEST_PARTICULAR}/${test_case}`);
          let time2 = new Date().getTime();
          time_tot += (time2 - time1);
        }
        fs.writeFile(out_particular_optimizations, `${file_particular};${test_case};${time_tot/50.0}\n`);
      } catch(err) {
        console.log(err)
      }
    })
  })
}

function base_geral_run() {
  let time1, time2;
  tests_cases.forEach((test_case)=> {
    try {
      let time_tot = 0;
      for(let i = 0; i < 50; i++) {
        let time1 = new Date().getTime();
        execSync(`./${DIRECTORY_BIN_BASE}/${base_geral} < ${DIRECTORY_TEST_GENERAL}/${test_case}`);
        let time2 = new Date().getTime();
        time_tot += (time2 - time1);
      }
      fs.writeFile(out_general_base, `${base_geral};${test_case};${time_tot/50.0}\n`);
    } catch(err) {
      console.log(err)
    }
  })
}

function base_particular_run() {
  let time1, time2;
  tests_cases.forEach((test_case)=> {
    try {
      let time_tot = 0;
      for(let i = 0; i < 50; i++) {
        let time1 = new Date().getTime();
        execSync(`./${DIRECTORY_BIN_BASE}/${base_particular} < ${DIRECTORY_TEST_PARTICULAR}/${test_case}`);
        let time2 = new Date().getTime();
        time_tot += (time2 - time1);
      }
      fs.writeFile(out_particular_base, `${base_particular};${test_case};${time_tot/50.0}\n`);
    } catch(err) {
      console.log(err)
    }
  })
}

opt_particulars_run()
base_particular_run()
