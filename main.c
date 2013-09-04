#include <stdio.h>

/* general pseudocode:
 * main
 *  switch (argc)
 *      case 0:
 *      no_param;
 *      break;
 *      case 1:
 *      one_param;
 *      break;
 *      case 2:
 *      two_param;
 *      break;
 *      default:
 *      error;
 *
 *
 * no_param
 *  prompt src
 *  if (src is NOT blank) {
 *      one_param(src)
 *  }
 *  one_param
 *  check_or_add_ext(src)
 *  prompt tar
 *  if (tar is blank) {
 *      tar = generate_target_filename(src, "IN");
 *  }
 *  check_or_add_ext(tar)
 *  two_param(src, tar)
 *
 * two_param
 *  check_or_add_ext(src,"OUT")
 *  check_or_add_ext(tar,"IN")
 *  if (file_exists(tar)) {
 *   backup(tar)
 *   open(tar)
 *   open(src)
 *   write(src, tar);
 *   if (src is open) close(src)
 *   if (tar is open) close(tar)
 *  }
 */

int main(int argc, char * argv[]) {
	printf("\nUsage: %s [input_file [output_file]]\n", argv[0]);
    switch (argc) {
        case 3:
            handle_two_params(argv[1], argv[2]);
        break;
        case 2:
            handle_one_params(argv[1]);
        break;
        case 1:
        default:
            handle_no_params();
    }
    return 0;
}
