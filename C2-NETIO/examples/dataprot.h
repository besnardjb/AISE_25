typedef enum
{
	MSG_METRIC_MSG_DESC, 
	MSG_METRIC_MSG_VAL,
}MSG_metric_msg_type_t;

static const char const MSG_metric_msg_type_name[] =
{
	"MSG_METRIC_MSG_DESC",
	"MSG_METRIC_MSG_VAL",
};

typedef struct {
	char name[METRIC_STRING_SIZE];
	char doc[METRIC_STRING_SIZE];
	int type;
}MSG_metric_descriptor_t;

typedef struct {
	char name[METRIC_STRING_SIZE];
	double value;
	double update_ts;
}MSG_metric_event_t;

typedef struct {
	MSG_metric_msg_type_t type;
	union {
		MSG_metric_descriptor_t desc;
		MSG_metric_event_t event;
	}payload;
	char canary;
}MSG_metric_msg_t;
