/* check_roman_calculator.c */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../src/roman_calculator.h"

static void assert_sum_equals(const char *summand1, const char *summand2,
                const char *expected_sum);
static void assert_difference_equals(const char *numeral1, const char *numeral2,
                const char *expected_difference);

/*
 * Tests for add_roman_numerals
 */

START_TEST(addition_function_accepts_two_strings)
    char *sum = add_roman_numerals("I", "I");
    free(sum);
END_TEST

START_TEST(sum_of_I_and_I_is_II)
    assert_sum_equals("I", "I", "II");
END_TEST

START_TEST(sum_of_II_and_I_is_III)
    assert_sum_equals("II", "I", "III");
END_TEST

START_TEST(can_carryover_from_a_numeral_to_the_next_greatest_when_adding)
    assert_sum_equals("III", "II", "V");
    assert_sum_equals("V", "V", "X");
    assert_sum_equals("XXX", "XX", "L");
    assert_sum_equals("L", "L", "C");
    assert_sum_equals("CCC", "CC", "D");
    assert_sum_equals("D", "D", "M");
END_TEST

START_TEST(sum_of_II_and_II_is_IV)
    assert_sum_equals("II", "II", "IV");
END_TEST

START_TEST(sum_of_XX_and_XX_is_XL)
    assert_sum_equals("XX", "XX", "XL");
END_TEST

START_TEST(sum_of_DC_and_CCC_is_CM)
    assert_sum_equals("DC", "CCC", "CM");
END_TEST

START_TEST(sum_of_IV_and_I_is_V)
    assert_sum_equals("IV", "I", "V");
END_TEST

START_TEST(sum_of_IX_and_I_is_X)
    assert_sum_equals("IX", "I", "X");
END_TEST

START_TEST(sum_of_XC_and_X_is_C)
    assert_sum_equals("XC", "X", "C");
END_TEST

START_TEST(add_roman_numerals_exits_with_a_failure_state_when_first_argument_is_malformed)
    add_roman_numerals("not a Roman numeral", "I");
END_TEST

START_TEST(add_roman_numerals_exits_with_a_failure_state_when_second_argument_is_malformed)
    add_roman_numerals("I", "also not a Roman numeral");
END_TEST

START_TEST(empty_addition_input_strings_result_in_failure)
    assert_sum_equals("", "I", "I");
    assert_sum_equals("I", "", "I");
    assert_sum_equals("", "", "");
END_TEST

START_TEST(sum_of_I_and_XLI_is_XLII)
    assert_sum_equals("I", "XLI", "XLII");
END_TEST

START_TEST(add_roman_numerals_accepts_input_greater_than_3999)
    assert_sum_equals("MMMM", "MMMMM", "MMMMMMMMM");
END_TEST

START_TEST(sum_of_MMD_and_MMD_is_MMMMM)
    assert_sum_equals("MMD", "MMD", "MMMMM");
END_TEST

/*
 * Tests for subtract_roman_numerals
 */

START_TEST(subtraction_function_accepts_two_strings)
    char *difference = subtract_roman_numerals("II", "I");
    free(difference);
END_TEST

START_TEST(II_minus_I_is_I)
    assert_difference_equals("II", "I", "I");
END_TEST

START_TEST(III_minus_I_is_II)
    assert_difference_equals("III", "I", "II");
END_TEST

START_TEST(VI_minus_I_is_V)
    assert_difference_equals("VI", "I", "V");
END_TEST

START_TEST(V_minus_II_is_III)
    assert_difference_equals("V", "II", "III");
END_TEST

START_TEST(V_minus_III_is_II)
    assert_difference_equals("V", "III", "II");
END_TEST

START_TEST(borrowing_is_performed_correctly_when_subtracting_one_roman_char_from_another)
    assert_difference_equals("V", "I", "IV");
    assert_difference_equals("X", "I", "IX");
    assert_difference_equals("X", "V", "V");
    assert_difference_equals("L", "I", "XLIX");
    assert_difference_equals("L", "V", "XLV");
    assert_difference_equals("C", "I", "XCIX");
    assert_difference_equals("C", "V", "XCV");
    assert_difference_equals("C", "L", "L");
    assert_difference_equals("D", "I", "CDXCIX");
    assert_difference_equals("D", "V", "CDXCV");
    assert_difference_equals("D", "L", "CDL");
    assert_difference_equals("M", "I", "CMXCIX");
    assert_difference_equals("M", "V", "CMXCV");
    assert_difference_equals("M", "L", "CML");
    assert_difference_equals("M", "D", "D");
END_TEST

START_TEST(subtract_roman_numerals_rejects_non_Roman_numeral_input)
    subtract_roman_numerals("these are not", "Roman numerals");
END_TEST

START_TEST(IX_minus_V_is_IV)
    assert_difference_equals("IX", "V", "IV");
END_TEST

START_TEST(XV_minus_IX_equals_VI)
    assert_difference_equals("XV", "IX", "VI");
END_TEST

START_TEST(subtract_roman_numerals_accepts_input_greater_than_3999)
    assert_difference_equals("MMMMMMMMM", "MMMMM", "MMMM");
END_TEST

START_TEST(MMMMM_minus_MMC_equals_MMCM)
    assert_difference_equals("MMMMM", "MMC", "MMCM");
END_TEST

static void assert_sum_equals(const char *summand1, const char *summand2,
                              const char *expected_sum)
{
    char *sum = add_roman_numerals(summand1, summand2);
    ck_assert_str_eq(sum, expected_sum);
    free(sum);
}

static void assert_difference_equals(const char *numeral1, const char *numeral2,
                                     const char *expected_difference)
{
    char *difference = subtract_roman_numerals(numeral1, numeral2);
    ck_assert_str_eq(difference, expected_difference);
    free(difference);
}

Suite *create_calculator_test_suite(void)
{
    Suite *test_suite = suite_create("Roman_Calculator");

    TCase *addition_test_case = tcase_create("Addition");
    TCase *subtraction_test_case = tcase_create("Subtraction");

    /*
     * Populate addition test case
     */
    tcase_add_test(addition_test_case, addition_function_accepts_two_strings);
    tcase_add_test(addition_test_case, sum_of_I_and_I_is_II);
    tcase_add_test(addition_test_case, sum_of_II_and_I_is_III);
    tcase_add_test(
        addition_test_case,
        can_carryover_from_a_numeral_to_the_next_greatest_when_adding
    );
    tcase_add_test(addition_test_case, sum_of_II_and_II_is_IV);
    tcase_add_test(addition_test_case, sum_of_XX_and_XX_is_XL);
    tcase_add_test(addition_test_case, sum_of_DC_and_CCC_is_CM);
    tcase_add_test(addition_test_case, sum_of_IV_and_I_is_V);
    tcase_add_test(addition_test_case, sum_of_IX_and_I_is_X);
    tcase_add_test(addition_test_case, sum_of_XC_and_X_is_C);
    tcase_add_exit_test(
        addition_test_case,
        add_roman_numerals_exits_with_a_failure_state_when_first_argument_is_malformed,
        EXIT_FAILURE
    );
    tcase_add_exit_test(
        addition_test_case,
        add_roman_numerals_exits_with_a_failure_state_when_second_argument_is_malformed,
        EXIT_FAILURE
    );
    tcase_add_exit_test(
        addition_test_case,
        empty_addition_input_strings_result_in_failure,
        EXIT_FAILURE
    );
    tcase_add_test(addition_test_case, sum_of_I_and_XLI_is_XLII);
    tcase_add_test(
        addition_test_case,
        add_roman_numerals_accepts_input_greater_than_3999
    );
    tcase_add_test(addition_test_case, sum_of_MMD_and_MMD_is_MMMMM);

    /*
     * Populate subtraction test case
     */
    tcase_add_test(
        subtraction_test_case,
        subtraction_function_accepts_two_strings
    );
    tcase_add_test(subtraction_test_case, II_minus_I_is_I);
    tcase_add_test(subtraction_test_case, III_minus_I_is_II);
    tcase_add_test(subtraction_test_case, VI_minus_I_is_V);
    tcase_add_test(subtraction_test_case, V_minus_II_is_III);
    tcase_add_test(subtraction_test_case, V_minus_III_is_II);
    tcase_add_test(
        subtraction_test_case,
        borrowing_is_performed_correctly_when_subtracting_one_roman_char_from_another
    );
    tcase_add_exit_test(
        subtraction_test_case,
        subtract_roman_numerals_rejects_non_Roman_numeral_input,
        EXIT_FAILURE
    );
    tcase_add_test(subtraction_test_case, IX_minus_V_is_IV);
    tcase_add_test(subtraction_test_case, XV_minus_IX_equals_VI);
    tcase_add_test(
        subtraction_test_case,
        subtract_roman_numerals_accepts_input_greater_than_3999
    );
    tcase_add_test(subtraction_test_case, MMMMM_minus_MMC_equals_MMCM);

    suite_add_tcase(test_suite, addition_test_case);
    suite_add_tcase(test_suite, subtraction_test_case);

    return test_suite;
}

int main(void)
{
    int failure_count = 0;
    Suite *test_suite = create_calculator_test_suite();
    SRunner *suite_runner = srunner_create(test_suite);
    srunner_run_all(suite_runner, CK_NORMAL);

    failure_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    return (failure_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
