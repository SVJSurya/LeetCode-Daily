with cte as(
    select requester_id as friends
    from RequestAccepted
    union all
    select accepter_id as friends
    from RequestAccepted
)
select 
    friends as id,
    count(friends) as num
from cte
group by friends
order by num desc
limit 1;