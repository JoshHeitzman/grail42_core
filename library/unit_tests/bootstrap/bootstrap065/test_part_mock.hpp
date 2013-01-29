class test_part_mock_with_id : public G42CORE_TEST_NS detail::test_part_base_common
{
G42CORE_MC_NOT_COPYABLE(test_part_mock_with_id)
public:
    test_part_mock_with_id(const char* id):
        test_part_base_common(
            id,
            G42CORE_TEST_NS detail::logical_process_and_thread_holder(0, 0), 
            G42CORE_TEST_NS detail::basic_source_code_info_holder("", 0))
    {}

    ~test_part_mock_with_id() {}

    virtual void run() const
    {
    }
};


