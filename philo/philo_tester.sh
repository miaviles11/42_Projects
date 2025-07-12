#!/bin/bash

# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   philo_tester.sh                                    :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025/07/12 by miaviles                   #+#    #+#             #
#   Updated: 2025/07/12 by miaviles                  ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Configuration
PHILO_PATH="./philo"
TIMEOUT_CMD="timeout"
LOG_DIR="test_logs"

# Create log directory
mkdir -p $LOG_DIR

print_header() {
    echo -e "${CYAN}================================${NC}"
    echo -e "${CYAN}    PHILOSOPHERS TESTER V2.0    ${NC}"
    echo -e "${CYAN}================================${NC}\n"
}

print_test_header() {
    echo -e "${BLUE}--- $1 ---${NC}"
}

print_result() {
    local test_name="$1"
    local result="$2"
    local details="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$result" = "PASS" ]; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        [ -n "$details" ] && echo -e "  ${YELLOW}Details: $details${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

check_compilation() {
    print_test_header "COMPILATION TESTS"
    
    # Check if Makefile exists
    if [ ! -f "Makefile" ]; then
        print_result "Makefile exists" "FAIL" "Makefile not found"
        return 1
    fi
    print_result "Makefile exists" "PASS"
    
    # Test make
    make > $LOG_DIR/make.log 2>&1
    if [ $? -eq 0 ] && [ -f "$PHILO_PATH" ]; then
        print_result "make compilation" "PASS"
    else
        print_result "make compilation" "FAIL" "Check $LOG_DIR/make.log"
        return 1
    fi
    
    # Test make clean
    make clean > /dev/null 2>&1
    if ls *.o > /dev/null 2>&1; then
        print_result "make clean" "FAIL" "Object files still present"
    else
        print_result "make clean" "PASS"
    fi
    
    # Test make fclean
    make fclean > /dev/null 2>&1
    if [ -f "$PHILO_PATH" ]; then
        print_result "make fclean" "FAIL" "Executable still present"
    else
        print_result "make fclean" "PASS"
    fi
    
    # Test make re
    make re > $LOG_DIR/make_re.log 2>&1
    if [ $? -eq 0 ] && [ -f "$PHILO_PATH" ]; then
        print_result "make re" "PASS"
    else
        print_result "make re" "FAIL" "Check $LOG_DIR/make_re.log"
        return 1
    fi
    
    echo ""
    return 0
}

check_argument_validation() {
    print_test_header "ARGUMENT VALIDATION TESTS"
    
    # No arguments
    $PHILO_PATH > $LOG_DIR/no_args.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "No arguments" "PASS"
    else
        print_result "No arguments" "FAIL" "Should return error"
    fi
    
    # Too few arguments
    $PHILO_PATH 5 800 200 > $LOG_DIR/few_args.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "Too few arguments" "PASS"
    else
        print_result "Too few arguments" "FAIL" "Should return error"
    fi
    
    # Too many arguments
    $PHILO_PATH 5 800 200 200 7 extra > $LOG_DIR/many_args.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "Too many arguments" "PASS"
    else
        print_result "Too many arguments" "FAIL" "Should return error"
    fi
    
    # Negative numbers
    $PHILO_PATH -5 800 200 200 > $LOG_DIR/negative.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "Negative numbers" "PASS"
    else
        print_result "Negative numbers" "FAIL" "Should return error"
    fi
    
    # Zero philosophers
    $PHILO_PATH 0 800 200 200 > $LOG_DIR/zero_philos.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "Zero philosophers" "PASS"
    else
        print_result "Zero philosophers" "FAIL" "Should return error"
    fi
    
    # Non-numeric arguments
    $PHILO_PATH abc 800 200 200 > $LOG_DIR/non_numeric.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "Non-numeric arguments" "PASS"
    else
        print_result "Non-numeric arguments" "FAIL" "Should return error"
    fi
    
    # Very large numbers
    $PHILO_PATH 999999999999999999 800 200 200 > $LOG_DIR/overflow.log 2>&1
    if [ $? -ne 0 ]; then
        print_result "Integer overflow" "PASS"
    else
        print_result "Integer overflow" "FAIL" "Should handle overflow"
    fi
    
    echo ""
}

run_survival_test() {
    local args="$1"
    local test_name="$2"
    local max_time="$3"
    
    local log_file="$LOG_DIR/test_${test_name// /_}.log"
    
    echo -e "${YELLOW}Running: $PHILO_PATH $args${NC}"
    echo -e "${YELLOW}Should survive for ${max_time}s without deaths${NC}"
    
    local start_time=$(date +%s)
    $TIMEOUT_CMD ${max_time}s $PHILO_PATH $args > $log_file 2>&1
    local exit_code=$?
    local end_time=$(date +%s)
    local actual_duration=$((end_time - start_time))
    
    # Check for premature death
    if grep -q "died" $log_file; then
        local death_time=$(grep "died" $log_file | tail -1 | cut -d' ' -f1)
        local death_seconds=$((death_time / 1000))
        print_result "$test_name - No premature death" "FAIL" "Philosopher died at ${death_seconds}s"
        return 1
    else
        print_result "$test_name - No premature death" "PASS" "Survived ${actual_duration}s"
    fi
    
    # Check that it ran for expected time (should timeout)
    if [ $actual_duration -ge $((max_time - 1)) ]; then
        print_result "$test_name - Timing" "PASS" "Ran for ${actual_duration}s (timeout)"
    else
        print_result "$test_name - Timing" "FAIL" "Only ran for ${actual_duration}s, expected ${max_time}s"
    fi
    
    # Check for data races (basic check)
    if grep -qi "data race\|race condition\|sanitizer" $log_file; then
        print_result "$test_name - No data races" "FAIL" "Possible data race detected"
    else
        print_result "$test_name - No data races" "PASS"
    fi
    
    return 0
}

run_death_test() {
    local args="$1"
    local expected_death_time="$2"
    local test_name="$3"
    local tolerance="$4"
    local max_time="$5"
    
    local log_file="$LOG_DIR/test_${test_name// /_}.log"
    
    echo -e "${YELLOW}Running: $PHILO_PATH $args${NC}"
    echo -e "${YELLOW}Expected death around: ${expected_death_time}ms${NC}"
    
    $TIMEOUT_CMD ${max_time}s $PHILO_PATH $args > $log_file 2>&1
    
    if grep -q "died" $log_file; then
        local death_time=$(grep "died" $log_file | head -1 | cut -d' ' -f1)
        local lower_bound=$((expected_death_time - tolerance))
        local upper_bound=$((expected_death_time + tolerance))
        
        if [ $death_time -ge $lower_bound ] && [ $death_time -le $upper_bound ]; then
            print_result "$test_name - Death timing" "PASS" "Death at ${death_time}ms (expected ~${expected_death_time}ms)"
        else
            print_result "$test_name - Death timing" "FAIL" "Death at ${death_time}ms, expected ${expected_death_time}±${tolerance}ms"
        fi
        
        # Check single death
        local death_count=$(grep "died" $log_file | wc -l)
        if [ $death_count -eq 1 ]; then
            print_result "$test_name - Single death" "PASS"
        else
            print_result "$test_name - Single death" "FAIL" "Multiple deaths detected"
        fi
    else
        print_result "$test_name - Death detection" "FAIL" "No death detected"
    fi
}

check_basic_functionality() {
    print_test_header "BASIC FUNCTIONALITY TESTS"
    
    # Test 1: Single philosopher (should die) - OFFICIAL TEST
    echo -e "${YELLOW}Testing single philosopher case...${NC}"
    $TIMEOUT_CMD 3s $PHILO_PATH 1 800 200 200 > $LOG_DIR/single_philo.log 2>&1
    if grep -q "died" $LOG_DIR/single_philo.log; then
        local death_time=$(grep "died" $LOG_DIR/single_philo.log | cut -d' ' -f1)
        if [ $death_time -ge 750 ] && [ $death_time -le 850 ]; then
            print_result "1 800 200 200 - Dies correctly" "PASS" "Died at ${death_time}ms"
        else
            print_result "1 800 200 200 - Dies correctly" "FAIL" "Died at ${death_time}ms, expected ~800ms"
        fi
    else
        print_result "1 800 200 200 - Should die" "FAIL" "Should die after time_to_die"
    fi
    
    # Test 2: Five philosophers (should survive) - OFFICIAL TEST
    run_survival_test "5 800 200 200" "5 800 200 200 - No death" 6
    
    # Test 3: Must eat test - OFFICIAL TEST
    echo -e "${YELLOW}Testing must_eat functionality...${NC}"
    local log_file="$LOG_DIR/must_eat_official.log"
    $TIMEOUT_CMD 15s $PHILO_PATH 5 800 200 200 7 > $log_file 2>&1
    
    if ! grep -q "died" $log_file; then
        print_result "5 800 200 200 7 - No deaths" "PASS"
    else
        print_result "5 800 200 200 7 - No deaths" "FAIL" "Philosophers died during must_eat test"
    fi
    
    # Check that each philosopher ate at least 7 times
    local all_ate_enough=true
    for i in {1..5}; do
        local eat_count=$(grep "^[0-9]* $i is eating" $log_file | wc -l)
        if [ $eat_count -lt 7 ]; then
            all_ate_enough=false
            break
        fi
    done
    
    if [ "$all_ate_enough" = true ]; then
        print_result "5 800 200 200 7 - All ate 7+ times" "PASS"
    else
        print_result "5 800 200 200 7 - All ate 7+ times" "FAIL" "Not all philosophers ate enough times"
    fi
    
    # Test 4: Four philosophers (should survive) - OFFICIAL TEST
    run_survival_test "4 410 200 200" "4 410 200 200 - No death" 6
    
    # Test 5: Four philosophers tight timing (should die) - OFFICIAL TEST
    run_death_test "4 310 200 100" 310 "4 310 200 100 - Should die" 50 4
    
    echo ""
}

check_edge_cases() {
    print_test_header "EDGE CASE TESTS"
    
    # Your problematic case (should survive now)
    run_survival_test "3 320 103 103" "3 320 103 103 (your case)" 6
    
    # Large number of philosophers - should survive
    run_survival_test "50 800 200 200" "Many philosophers (50)" 8
    
    # Minimum allowed values (60ms minimum as per correction sheet)
    run_survival_test "4 120 60 60" "Minimum timing values" 4
    
    # Uneven philosophers - should survive
    run_survival_test "7 800 200 200" "Odd number philosophers (7)" 6
    
    # Stress case with many short-lived philosophers
    run_survival_test "10 400 100 100" "10 philosophers tight timing" 6
    
    echo ""
}

check_forbidden_tests() {
    print_test_header "BOUNDARY TESTS (As per correction sheet)"
    
    echo -e "${YELLOW}Note: Following correction sheet guidelines${NC}"
    echo -e "${YELLOW}• Not testing with >200 philosophers${NC}"
    echo -e "${YELLOW}• Not testing with values <60ms${NC}\n"
    
    # Test boundary values
    run_survival_test "200 800 200 200" "Maximum philosophers (200)" 10
    
    # Test minimum timing values (60ms minimum)
    run_survival_test "5 180 60 60" "Minimum timing (60ms)" 5
    
    # Test just above death threshold  
    run_survival_test "4 400 200 100" "Just above death threshold" 6
    
    echo ""
}

check_death_timing_precision() {
    print_test_header "DEATH TIMING PRECISION TESTS"
    
    echo -e "${YELLOW}Testing death timing precision (±10ms tolerance)...${NC}"
    
    # Test with 2 philosophers - OFFICIAL REQUIREMENT
    local log_file="$LOG_DIR/death_precision_2philos.log"
    $TIMEOUT_CMD 5s $PHILO_PATH 2 300 150 150 > $log_file 2>&1
    
    if grep -q "died" $log_file; then
        local death_time=$(grep "died" $log_file | head -1 | cut -d' ' -f1)
        local expected_death=300
        local tolerance=10
        
        if [ $death_time -ge $((expected_death - tolerance)) ] && [ $death_time -le $((expected_death + tolerance)) ]; then
            print_result "2 philosophers death timing (±10ms)" "PASS" "Death at ${death_time}ms (expected ${expected_death}±${tolerance}ms)"
        else
            print_result "2 philosophers death timing (±10ms)" "FAIL" "Death at ${death_time}ms, expected ${expected_death}±${tolerance}ms"
        fi
    else
        print_result "2 philosophers death timing test" "FAIL" "No death detected"
    fi
    
    # Test with different timing scenarios
    local scenarios=(
        "3 400 150 150 400"
        "4 500 200 200 500" 
        "2 250 100 100 250"
    )
    
    for scenario in "${scenarios[@]}"; do
        local args=$(echo $scenario | cut -d' ' -f1-4)
        local expected=$(echo $scenario | cut -d' ' -f5)
        local test_name="Death precision $args"
        
        echo -e "${YELLOW}Testing: $args (expected ~${expected}ms)${NC}"
        local log_file="$LOG_DIR/precision_${args// /_}.log"
        
        $TIMEOUT_CMD 4s $PHILO_PATH $args > $log_file 2>&1
        
        if grep -q "died" $log_file; then
            local death_time=$(grep "died" $log_file | head -1 | cut -d' ' -f1)
            local tolerance=15
            
            if [ $death_time -ge $((expected - tolerance)) ] && [ $death_time -le $((expected + tolerance)) ]; then
                print_result "$test_name" "PASS" "Death at ${death_time}ms"
            else
                print_result "$test_name" "FAIL" "Death at ${death_time}ms, expected ~${expected}ms"
            fi
        else
            print_result "$test_name" "FAIL" "No death detected"
        fi
    done
    
    echo ""
}

check_log_format() {
    print_test_header "LOG FORMAT TESTS"
    
    local log_file="$LOG_DIR/log_format.log"
    $TIMEOUT_CMD 3s $PHILO_PATH 4 800 200 200 > $log_file 2>&1
    
    # Check log format
    local format_correct=true
    local line_count=0
    
    while IFS= read -r line && [ $line_count -lt 50 ]; do
        if ! echo "$line" | grep -qE '^[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$'; then
            format_correct=false
            break
        fi
        line_count=$((line_count + 1))
    done < $log_file
    
    if [ "$format_correct" = true ]; then
        print_result "Log format correctness" "PASS"
    else
        print_result "Log format correctness" "FAIL" "Invalid log format detected"
    fi
    
    # Check timestamp order
    local timestamps_ordered=true
    local last_timestamp=0
    
    while IFS= read -r line && [ $line_count -lt 100 ]; do
        local timestamp=$(echo "$line" | cut -d' ' -f1)
        if [ $timestamp -lt $last_timestamp ]; then
            timestamps_ordered=false
            break
        fi
        last_timestamp=$timestamp
    done < $log_file
    
    if [ "$timestamps_ordered" = true ]; then
        print_result "Timestamp ordering" "PASS"
    else
        print_result "Timestamp ordering" "FAIL" "Timestamps not in order"
    fi
    
    echo ""
}

stress_test() {
    print_test_header "STRESS TESTS"
    
    echo -e "${YELLOW}Running stress tests (this may take a while)...${NC}"
    
    # Multiple rapid tests with longer duration
    local stress_passed=0
    local stress_total=15
    
    for i in $(seq 1 $stress_total); do
        echo -ne "${YELLOW}Stress test $i/$stress_total...\r${NC}"
        $TIMEOUT_CMD 5s $PHILO_PATH 5 800 200 200 > $LOG_DIR/stress_$i.log 2>&1
        if ! grep -q "died" $LOG_DIR/stress_$i.log; then
            stress_passed=$((stress_passed + 1))
        fi
    done
    
    echo ""
    if [ $stress_passed -eq $stress_total ]; then
        print_result "Stress test consistency" "PASS" "$stress_passed/$stress_total tests passed"
    else
        print_result "Stress test consistency" "FAIL" "Only $stress_passed/$stress_total tests passed"
    fi
    
    # Memory leak test (if valgrind available)
    if command -v valgrind > /dev/null; then
        echo -e "${YELLOW}Running valgrind memory leak test...${NC}"
        valgrind --leak-check=full --error-exitcode=1 $TIMEOUT_CMD 3s $PHILO_PATH 4 800 200 200 > $LOG_DIR/valgrind.log 2>&1
        if [ $? -eq 0 ]; then
            print_result "Memory leak test (valgrind)" "PASS"
        else
            print_result "Memory leak test (valgrind)" "FAIL" "Check $LOG_DIR/valgrind.log"
        fi
    else
        print_result "Memory leak test (valgrind)" "SKIP" "valgrind not available"
    fi
    
    # Data race test (if valgrind available)
    if command -v valgrind > /dev/null; then
        echo -e "${YELLOW}Running helgrind data race test...${NC}"
        valgrind --tool=helgrind --error-exitcode=1 $TIMEOUT_CMD 2s $PHILO_PATH 4 800 200 200 > $LOG_DIR/helgrind.log 2>&1
        if [ $? -eq 0 ]; then
            print_result "Data race test (helgrind)" "PASS"
        else
            print_result "Data race test (helgrind)" "FAIL" "Check $LOG_DIR/helgrind.log"
        fi
    else
        print_result "Data race test (helgrind)" "SKIP" "valgrind not available"
    fi
    
    echo ""
}

print_summary() {
    echo -e "${CYAN}================================${NC}"
    echo -e "${CYAN}           TEST SUMMARY          ${NC}"
    echo -e "${CYAN}================================${NC}"
    echo -e "Total tests: $TOTAL_TESTS"
    echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
    echo -e "${RED}Failed: $FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
        echo -e "${GREEN}Your philosophers simulation looks solid!${NC}"
    else
        echo -e "\n${RED}❌ Some tests failed.${NC}"
        echo -e "${YELLOW}Check the logs in $LOG_DIR/ for details.${NC}"
    fi
    
    echo -e "\n${BLUE}Logs saved in: $LOG_DIR/${NC}"
    echo -e "${CYAN}================================${NC}"
}

main() {
    print_header
    
    # Check if philo exists
    if [ ! -f "$PHILO_PATH" ]; then
        echo -e "${RED}Error: $PHILO_PATH not found. Please compile first.${NC}"
        echo -e "${YELLOW}Attempting to compile...${NC}"
        make > /dev/null 2>&1
        if [ ! -f "$PHILO_PATH" ]; then
            echo -e "${RED}Compilation failed. Exiting.${NC}"
            exit 1
        fi
    fi
    
    # Run test suites
    check_compilation
    check_argument_validation
    check_basic_functionality
    check_death_timing_precision
    check_edge_cases
    check_forbidden_tests
    check_log_format
    stress_test
    
    print_summary
}

# Handle Ctrl+C gracefully
trap 'echo -e "\n${YELLOW}Test interrupted by user.${NC}"; exit 1' INT

# Run main function
main "$@"