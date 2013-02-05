class test_part_mock_with_id : public G42CORE_TEST_NS detail::test_part_base_common
{
G42CORE_MC_NOT_COPYABLE(test_part_mock_with_id)
public:
    test_part_mock_with_id(const char* id, int threadId = G42CORE_TEST_NS detail::logical_process_and_thread_holder::special_thread_ids::any):
        test_part_base_common(
            id,
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(threadId, 0), 
            G42CORE_TEST_NS detail::basic_source_code_info_holder("", 0)),
        runCallCount(0),
        runShouldThrow(false)
    {}

    ~test_part_mock_with_id() {}

    virtual void run() const
    {
        ++(const_cast<test_part_mock_with_id*>(this)->runCallCount);
        if(runShouldThrow)
        {
            throw G42CORE_TEST_NS detail::verification_failure("mockfile", 55, "mockexp");
        }
    }

    unsigned int run_call_count() const
    {
        return runCallCount;
    }

    void run_should_throw(bool b)
    {
        runShouldThrow = b;
    }

private:
    unsigned int runCallCount;
    bool runShouldThrow;
};


