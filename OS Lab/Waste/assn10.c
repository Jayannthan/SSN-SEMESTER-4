#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct memory
{
	char page;
	struct memory * next;
};
void init_frame(struct memory *frame)
{
	struct memory *ptr = frame->next;
	while (ptr != NULL)
	{
		ptr->page = '-';
		ptr = ptr->next;
	}
}
void insert_frame(struct memory *frame, char page)
{
	struct memory *new_frame = (struct memory *) malloc(sizeof(struct memory));
	new_frame->page = page;
	new_frame->next = NULL;
	struct memory *ptr = frame;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new_frame;
}
void delete_frame(struct memory *frame)
{
	while (frame->next != NULL)
	{
		struct memory *temp = frame->next;
		frame->next = frame->next->next;
		free(temp);
	}
}
void replace(struct memory *frame, int cur_fault, char page)
{
	int count = 0;
	struct memory *ptr = frame->next;
	while (count < cur_fault && ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	if (ptr != NULL)
	{
		ptr->page = page;
	}
}
int present(struct memory *frame, int start, int end, char page)
{
	int count = 0;
	struct memory *ptr = frame->next;
	while (count != start)
	{
		count++;
		ptr = ptr->next;
	}
	while (count < end && ptr != NULL)
	{
		if (page == ptr->page)
		{
			return count;
		}
		count++;
		ptr = ptr->next;
	}
	return 100;
}
int present_ref(char str_ref[], int start, int end, char page)
{
	for (int i = start; i < end; i++)
	{
		if (page == str_ref[i])
		{
			return i;
		}
	}
	return 100;
}
int present_last(struct memory *frame, int start, int end, char page)
{
	int pos;
	int count = 0;
	struct memory *ptr = frame->next;
	while (count != start)
	{
		count++;
		ptr = ptr->next;
	}
	while (count <= end && ptr != NULL)
	{
		if (page == ptr->page)
		{
			pos = count;
		}
		count++;
		ptr = ptr->next;
	}
	return pos;
}
int present_last_ref(char ref_str[], int start, int end, char page)
{
	int pos;
	for (int i = start; i <= end; i++)
	{
		if (page == ref_str[i])
		{
			pos = i;
		}
	}
	return pos;
}
int max(int duration[], int page_follow[], int no_frames)
{
	int first = page_follow[0], first_pos = 0;
	for (int i = 0; i < no_frames; i++)
	{
		if (page_follow[i] > first)
		{
			first = page_follow[i];
			first_pos = i;
		}
	}
	if (page_follow[first_pos] == 100)
	{
		first = duration[first_pos];
		for (int i = 0; i < no_frames; i++)
		{
			if ((duration[i] > first) && (page_follow[i] == 100))
			{
				first = duration[i];
				first_pos = i;
			}
		}
	}
	return first_pos;
}
int min(int page_past[], int no_frames)
{
	int first = page_past[0], first_pos = 0;
	for (int i = 0; i < no_frames; i++)
	{
		if (page_past[i] < first)
		{
			first = page_past[i];
			first_pos = i;
		}
	}
	return first_pos;
}
int frequency(char ref_str[], int start, int end, char page)
{
	int freq = 0;
	for (int i = start; i <= end; i++)
	{
		if (page == ref_str[i])
		{
			freq++;
		}
	}
	return freq;
}
int min_freq(int duration[], int page_past[], int no_frames)
{
	int first = page_past[0], first_pos = 0, count = 0;
	for (int i = 0; i < no_frames; i++)
	{
		if (page_past[i] < first)
		{
			first = page_past[i];
			first_pos = i;
		}
	}
	for (int i = 0; i < no_frames; i++)
	{
		if (page_past[i] == page_past[first_pos])
		{
			count++;
		}
	}
	if (count >= 2)
	{
		first = duration[first_pos];
		int pos = 0;
		for (int i = 0; i < no_frames; i++)
		{
			if ((duration[i] > first) && (page_past[i] == page_past[pos]))
			{
				first = duration[i];
				pos = i;
			}
		}
		return pos;
	}
	return first_pos;
}
void print_frame(char page, struct memory *frame, int page_fault)
{
	printf("\n%c\t--->\t", page);
	struct memory *ptr = frame->next;
	while (ptr != NULL)
	{
		printf("%c\t", ptr->page);
		ptr = ptr->next;
	}
	if (!page_fault) {}
	else
	{
		printf("\tPage fault : %d", page_fault);
	}
}
char frame_page(struct memory *frame, int index)
{
	struct memory *ptr = frame->next;
	int count = 0;
	while (ptr != NULL && count < index)
	{
		ptr = ptr->next;
		count++;
	}
	return ptr->page;
}
void fifo(struct memory *frame, int no_frames, char ref_str[])
{
	init_frame(frame);
	int page_fault = 0, cur_fault = 0;
	for (int i = 0; ref_str[i] != '\0'; i++)
	{
		if (present(frame, 0, no_frames, ref_str[i]) == 100)
		{
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			cur_fault = (cur_fault + 1) % no_frames;
			print_frame(ref_str[i], frame, page_fault);
		}
		else
		{
			print_frame(ref_str[i], frame, 0);
		}
	}
	printf("\nTotal page faults : %d", page_fault);
}
void optimal(struct memory *frame, int no_frames, char ref_str[])
{
	init_frame(frame);
	int duration[100];
	for (int i = 0; i < no_frames; i++)
	{
		duration[i] = 0;
	}
	int page_fault = 0, cur_fault = 0;
	for (int i = 0; ref_str[i] != '\0'; i++)
	{
		if (present(frame, 0, no_frames, '-') != 100 && present(frame, 0,
				no_frames, ref_str[i]) == 100)
		{
			cur_fault = present(frame, 0, no_frames, '-');
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			print_frame(ref_str[i], frame, page_fault);
		}
		else if (present(frame, 0, no_frames, ref_str[i]) == 100)
		{
			int page_follow[100];
			for (int j = 0; j < no_frames; j++)
			{
				char item = frame_page(frame, j);
				page_follow[j] = present_ref(ref_str, i + 1, strlen(ref_str),
					item);
			}
			int cur_fault = max(duration, page_follow, no_frames);
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			for (int j = 0; j < no_frames; j++)
			{
				if (j != cur_fault)
				{
					duration[j]++;
				}
				else
				{
					duration[j] = 0;
				}
			}
			print_frame(ref_str[i], frame, page_fault);
		}
		else
		{
			print_frame(ref_str[i], frame, 0);
		}
	}
	printf("\nTotal page faults = %d", page_fault);
}
void lru(struct memory *frame, int no_frames, char ref_str[])
{
	init_frame(frame);
	int page_fault = 0, cur_fault = 0;
	for (int i = 0; ref_str[i] != '\0'; i++)
	{
		if (present(frame, 0, no_frames, '-') != 100 && present(frame, 0,
				no_frames, ref_str[i]) == 100)
		{
			cur_fault = present(frame, 0, no_frames, '-');
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			print_frame(ref_str[i], frame, page_fault);
		}
		else if (present(frame, 0, no_frames, ref_str[i]) == 100)
		{
			int page_follow[100];
			for (int j = 0; j < no_frames; j++)
			{
				char item = frame_page(frame, j);
				page_follow[j] = present_last_ref(ref_str, 0, i - 1, item);
			}
			int cur_fault = min(page_follow, no_frames);
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			print_frame(ref_str[i], frame, page_fault);
		}
		else
		{
			print_frame(ref_str[i], frame, 0);
		}
	}
	printf("\nTotal page faults = %d", page_fault);
}
void lfu(struct memory *frame, int no_frames, char ref_str[])
{
	init_frame(frame);
	int duration[100];
	for (int i = 0; i < no_frames; i++)
	{
		duration[i] = 0;
	}
	int page_fault = 0, cur_fault = 0;
	for (int i = 0; ref_str[i] != '\0'; i++)
	{
		if (present(frame, 0, no_frames, '-') != 100 && present(frame, 0,
				no_frames, ref_str[i]) == 100)
		{
			cur_fault = present(frame, 0, no_frames, '-');
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			print_frame(ref_str[i], frame, page_fault);
		}
		else if (present(frame, 0, no_frames, ref_str[i]) == 100)
		{
			int page_past[100];	//Finding frequency of page usage
			for (int j = 0; j < no_frames; j++)
			{
				char item = frame_page(frame, j);
				page_past[j] = frequency(ref_str, 0, i - 1, item);
			}
			int cur_fault = min_freq(duration, page_past, no_frames);
			replace(frame, cur_fault, ref_str[i]);
			page_fault++;
			for (int j = 0; j < no_frames; j++)
			{
				if (j != cur_fault)
				{
					duration[j]++;
				}
				else
				{
					duration[j] = 0;
				}
			}
			print_frame(ref_str[i], frame, page_fault);
		}
		else
		{
			print_frame(ref_str[i], frame, 0);
		}
	}
	printf("\nTotal page faults = %d", page_fault);
}
int main()
{
	struct memory *frame = (struct memory *) malloc(sizeof(struct memory));
	int no_frames, ref_len;
	char frames[100], ref_str[100];

	delete_frame(frame);
	printf("Number of frames: ");
	scanf(" %d", &no_frames);
	for (int i = 0; i < no_frames; i++)
	{
		insert_frame(frame, '-');
	}
	printf("\nReference string length: ");
	scanf(" %d", &ref_len);
	printf("\nReference string: ");
	for (int i = 0; i < ref_len; i++)
	{
		scanf(" %c", &ref_str[i]);
	}
	ref_str[ref_len] = '\0';

	while (1)
	{
		printf("\n1. FIFO\n2. Optimal\n3. LRU\n4. LFU\n5.Exit\nEnter your choice: ");
		int ch;
		scanf(" %d", &ch);
		switch (ch)
		{
			case 1:
				{
					fifo(frame, no_frames, ref_str);
					break;
				}
			case 2:
				{
					optimal(frame, no_frames, ref_str);
					break;
				}
			case 3:
				{
					lru(frame, no_frames, ref_str);
					break;
				}
			case 4:
				{
					lfu(frame, no_frames, ref_str);
					break;
				}
			case 5:
				{
					exit(1);
					break;
				}
			default:
				{
					printf("\nInvalid choice!");
					break;
				}
		}
	}
	printf("\n");
	return 0;
}
